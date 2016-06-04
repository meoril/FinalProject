/*
 * Particle.cpp
 *
 *  Created on: May 31, 2016
 *      Author: user
 */

#include "Particle.h"
#include "../Utils/BaseUtils.h"
#include <iostream>
#include <libplayerc++/playerc++.h>
using namespace PlayerCc;
using namespace std;


float probabilityByMovement(double x, double y)
{

	float distance = sqrt(pow((double)x,2) + pow((double)y,2));

	if (distance < 1)
		return 1;

	if (distance < 3)
		return 0.9;

	if (distance < 5)
		return 0.7;

	if (distance < 7)
		return 0.5;

	if (distance < 9)
		return 0.3;

	return 0.1;
}

float probabilityByLaserScan(Position* pos, const Map* map, const LaserProxy* laserProxy) {
	int xCoord = floor(pos->getX());
	int yCoord = floor(pos->getY());

	// In case we are out of bound, return a low probability.
	if (pos->getX() < 0 || pos->getX()>= map->width ||
			pos->getY() < 0 || pos->getY() >= map->height)
	{
		return 0;
	}

	// In case there is an obstacle in this point, return a low probability.
	if (map->RegGrid[yCoord][xCoord] == 1)
	{
		return 0;
	}

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
			else if (map->RegGrid[floor(obstacleY)][floor(obstacleX)] == 1)
			{
				correctHits++;
			}
		}
	}

	float accuracy = correctHits / totalHits;

	return accuracy;
}

float Random(float min, float max)
{
    float num = (float)rand() / RAND_MAX;
    return min + num * (max - min);
}

Particle::Particle(double xPos, double yPos, double yaw)
	: m_pos(xPos,yPos,yaw)
{
	this->m_belief = -1;
	this->m_age = 1;
}

float Particle::getBelief(){
	return this->m_belief;
}
	void Particle::Update(double deltaX, double deltaY, double deltaYaw, const Map* map, const LaserProxy* laser){
		this->m_pos.m_Yaw += deltaYaw;
		this->m_pos.m_Pnt.m_X +=deltaX;
		this->m_pos.m_Pnt.m_Y +=deltaY;

		// Calculating probability
		float probability = probabilityByLaserScan(&this->m_pos, map, laser) *
						probabilityByMovement(deltaX,deltaY) * 1.2;
		// Setting belief
		if (probability > 1){
			this->m_belief = 1;
		}


	}
	Particle* Particle::CreateChild(const int expansionRadius, const int yawRange)
	{
		   float newX = this->m_pos.getX() + Random(-expansionRadius, expansionRadius);
		    float newY = this->m_pos.getY() + Random(-expansionRadius, expansionRadius);
		    float newYaw = this->m_pos.getYaw() + Random(-yawRange, yawRange);
		    return new Particle(newX, newY, newYaw);
	}

