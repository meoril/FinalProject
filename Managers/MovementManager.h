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
    MovementManager(Robot* myinRobot);
    virtual ~MovementManager();
    int moveToNextWatPoint(Point *pDest, LocalizationManager *loc);

private:
    Robot *myrobot;
    static const double TOLERANCE = 20;
    static const double SLOWSPEEDRANGE = 10;
    static const double LINEARSPEED = 0.8;
    static const double SLOWSPEEDRATIO = 0.1;
    static const double DEGREETOLERANCE = 1;
    static const double YAWSPEED = 0.02;

};


#endif /* MOVEMENTMANAGER_H_ */
