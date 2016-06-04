/*
 * LocalizationManager.cpp
 *
 *  Created on: May 31, 2016
 *      Author: user
 */


#include "LocalizationManager.h"
#include <math.h>
#include "../Utils/BaseUtils.h"
using namespace PlayerCc;
using namespace std;
namespace Managers {

float ProbabilityByLaserScan(float xDelta, float yDelta, float yawDelta,  Map* map, LaserProxy* laserProxy)
{
	float x = xDelta;
	float y = yDelta;

	int xCoord = floor(x);
	int yCoord = floor(y);

	// In case we are out of bound, return a low probability.
	if (x < 0 || x >= map->width ||
	    y < 0 || y >= map->height)
	{
		return 0;
	}

	//vector< vector<Map::CELL_TYPE> > grid = map->MapMatrix;

	// In case there is an obstacle in this point, return a low probability.
	//if (grid[yCoord][xCoord] == 1)
	{
		return 0;
	}

	int scans = laserProxy->GetCount();
	float maxRange = laserProxy->GetMaxRange();

	float totalHits = 0;
	float correctHits = 0;
	int boundaryMisses = 0;
	for(int i=0; i < scans; i++)
	{
		float range = laserProxy->GetRange(i);

		if (range < maxRange)
		{
			totalHits++;

			float bearing = laserProxy->GetBearing(i);

			float rangeInPixels = BaseUtils::MeterToPixel(range);
			float yawInRadians = BaseUtils::DegreeToRadian(yawDelta);

			float obstacleX = xDelta + rangeInPixels * cos(yawInRadians + bearing);
			float obstacleY = yDelta - rangeInPixels * sin(yawInRadians + bearing);

			// Check if we missed boundaries.
			if ((obstacleX) < 0 || (obstacleX) >= map->width -10 ||
					obstacleY < 0 || (obstacleY) >= map->height -10)
			{
				boundaryMisses++;

				continue;
			}

			// Check if there's a hit on an obstacle.
			if (map->RegGrid[floor(obstacleY)][floor(obstacleX)] == 1)
			{

				correctHits++;
			}
		}
	}

	float accuracy = correctHits / totalHits;

	return accuracy;

}
}


LocalizationManager::LocalizationManager(){

}
void LocalizationManager::update(double deltaX, double deltaY, double deltaYaw){
}
void LocalizationManager::resampleParticles(){

	}
	Particle* LocalizationManager::getBestParticle(){
		return 0;
	}
	LocalizationManager::~LocalizationManager(){

	}
}

