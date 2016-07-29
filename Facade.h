/*
 * Facade.h
 *
 *  Created on: May 31, 2016
 *      Author: colman
 */


#ifndef FACADE_H_
#define FACADE_H_
#include "Models/Map.h"
#include "Models/Point.h"
#include "Models/Robot.h"
#include "Utils/PathPlanner.h"
#include "Managers/ConfigurationManager.h"
#include "Models/Robot.h"
#include "Managers/WaypointManager.h"
#include "Managers/LocalizationManager.h"
#include "Managers/MovementManager.h"
#include "Models/Node.h"


class Facade {
    public:
    Facade();
    virtual ~Facade();
    void Run();
    std::list<Node*> lstClearWaypointToDestination;
    void printPath(std::list<Node*>& lstStarPath, std::string name);
    private:
    Map* myMap;
    ConfigurationManager* myConfig;
    Robot* myRobot;
    LocalizationManager* locManager;
    MovementManager* moveManager;
};

#endif /* FACADE_H_ */
