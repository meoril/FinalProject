/*
 * Facade.cpp
 *
 *  Created on: May 31, 2016
 *      Author: colman
 */

#include "Facade.h"

Facade::Facade() {
    myConfig = new ConfigurationManager("Resources/Parameters.txt");
    myMap = new Map(myConfig);
    myRobot = new Robot("127.0.0.1", 6555, myConfig->getStartPosition(), myConfig->getGoal(), myConfig->getRobotSize(), true);
    
}

Facade::~Facade() {
}

void Facade::Run(){
    PathPlanner* pathPlanner = new PathPlanner();
    //std::list<Node*> lstStartWaypoints = pathPlanner->AStarPath();
}
