/*
 * MovementManager.h
 *
 *  Created on: Jun 11, 2016
 *      Author: colman
 */

#ifndef MOVEMENTMANAGER_H_
#define MOVEMENTMANAGER_H_

#include "../Models/Robot.h"
#include "../Managers/LocalizationManager.h"
#include "../Models/Position.h"

class MovementManager {
public:
	MovementManager();
	virtual ~MovementManager();
	void moveToNextWatPoint(int nXdest, int nYdest, LocalizationManager *loc);

private:
	Robot *myrobot;
	const double TOLERANCE = 0.01;
	const double SLOWSPEEDRANGE = 10 * TOLERANCE;
	const double LINEARSPEED = 0.8;
	const double SLOWSPEEDRATIO = 0.1;
	const double DEGREETOLERANCE = 1;
	const double YAWSPEED = 0.2;

};


#endif /* MOVEMENTMANAGER_H_ */
