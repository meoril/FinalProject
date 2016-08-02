/*
 * Particle.cpp
 *
 *  Created on: May 31, 2016
 *      Author: user
 */

#include "Particle.h"
#include "../Utils/BaseUtils.h"
#include <utility>
#include <iostream>
#include <libplayerc++/playerc++.h>
using namespace PlayerCc;
using namespace std;


float probabilityByMovement(double x, double y)
{

	float distance = sqrt(pow((double)x,2) + pow((double)y,2));


	if (distance < 5)
		return 1;

	if (distance < 15)
		return 0.92;

	if(distance < 25)
		return 0.85;

	if (distance < 30)
		return 0.83;

	if (distance < 40)
		return 0.80;

	if (distance < 47)
		return 0.75;

	if (distance < 65)
		return 0.7;

	if (distance < 80)
		return 0.2;

	if (distance < 110)
		return 0.4;

	return 0.1;
}
bool checkForObstacles(Position* pos,Map* map){
		// In case we are out of bound, return a low probability.
		if (pos->getX() < 0 || pos->getX()>= map->width ||
				pos->getY() < 0 || pos->getY() >= map->height)
		{
			return true;
		}

		// In case there is an obstacle in this point, return a low probability.
		if (map->isPointOccupiedInMap(&pos->m_Pnt))
		{
			return true;
		}

		return false;
}
float probabilityByLaserScan(Position* pos, const Map* map, const LaserProxy* laserProxy) {
	int scans = laserProxy->GetCount();
	float maxRange = laserProxy->GetMaxRange();

	float totalHits = 0;
	float correctHits = 0;
	int boundaryMisses = 0;

	// Checking for hits
	for(int i=0; i < scans; i++)
	{
		float range = laserProxy->GetRange(i);

		if (range < maxRange)
		{
			totalHits++;

			float bearing = laserProxy->GetBearing(i);

			// Calculating pixels and radians
			float rangeInPixels = BaseUtils::MeterToPixel(range);
			float yawInRadians = BaseUtils::DegreeToRadian(pos->m_Yaw);

			float obstacleX = pos->getX() + rangeInPixels * cos(yawInRadians + bearing);
			float obstacleY = pos->getY() - rangeInPixels * sin(yawInRadians + bearing);


			// Check if we missed boundaries.
			if ((obstacleX) < 0 || (obstacleX) >= map->width -10 ||
					obstacleY < 0 || (obstacleY) >= map->height -10)
			{
				boundaryMisses++;
			}
			// Check if there's a hit on an obstacle.
			else if (map->RegGrid[floor(obstacleX / 4)][floor(obstacleY / 4)] == 1)
			{
				correctHits++;
			}
		}
	}

	float accuracy = correctHits / totalHits;
	//cout << "Acc " << accuracy << endl;
	return std::max((float)accuracy,(float)0.001);
}

float Random(float min, float max)
{
    float num = (float)rand() / RAND_MAX;
    return min + num * (max - min);
}

Particle::~Particle(){

}
Particle::Particle(double xPos, double yPos, double yaw)
	: m_pos(xPos,yPos,yaw)
{
	this->m_belief = -1;
	this->m_age = 0;
}

float Particle::getBelief(){
	return this->m_belief;
}
	void Particle::Update(double deltaX, double deltaY, double deltaYaw, Map* map, const LaserProxy* laser){
		this->m_pos.m_Yaw += deltaYaw;
		this->m_pos.m_Pnt.m_X +=deltaX;
		this->m_pos.m_Pnt.m_Y +=deltaY;

		if (checkForObstacles(&this->m_pos, map))
		{
			this->m_belief = 0;
		}
		else {

			// Calculating probability
			this->m_belief = std::min(probabilityByLaserScan(&this->m_pos, map, laser) *
									 probabilityByMovement(deltaX,deltaY) * 12.2,(double)1);
			//this->m_belief = std::min(this->m_belief*( probabilityByLaserScan(&this->m_pos, map, laser) *
							//					 probabilityByMovement(deltaX,deltaY) * 12.2),(double)1);
			//cout << this->m_belief <<endl;
			if (this->m_belief == 1){
			//	cout << "Zivos" <<endl;
			}
			//cout << "Curr particle: " << this->m_belief << ", " << this->m_pos.getX()<< " " << this->m_pos.getY() << endl;
		}
		//cout << "Curr particle: " << this->m_belief << ", " << this->m_pos.getX()<< " " << this->m_pos.getY() << endl;
	}

Particle* Particle::CreateChild(const int expansionRadius, const int yawRange)
{
	   float newX = this->m_pos.getX() + Random(-expansionRadius, expansionRadius);
	    float newY = this->m_pos.getY() + Random(-expansionRadius, expansionRadius);
	    float newYaw = this->m_pos.getYaw() + Random(-yawRange, yawRange);
	    return new Particle(newX, newY, m_pos.getYaw());
}

Position Particle::getPosition(){
	return this->m_pos;
}

