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
    Point* tempStartPoint = new Point(myConfig->getStartPositionInGrid().getX(), myConfig->getStartPositionInGrid().getY());
    std::list<Node*> lstStartWaypoints = pathPlanner->AStarPath(*tempStartPoint, myConfig->getGoalInGrid(), myMap);
    lstStartWaypoints = pathPlanner->AStarClearList(lstStartWaypoints, myConfig->getGoalInGrid());
    
    this->printPath(*tempStartPoint, myConfig->getGoalInGrid());
}

void Facade::printPath(Point startPoint, Point endPoint){
    // Start location
    myMap->FatImage[(myConfig->getStartPositionInGrid().getX() * 4 + myConfig->getStartPositionInGrid().getY() * myMap->width * 4) + 0] = 255;
    myMap->FatImage[(myConfig->getStartPositionInGrid().getX() * 4 + myConfig->getStartPositionInGrid().getY() * myMap->width * 4) + 1] = 0;
    myMap->FatImage[(myConfig->getStartPositionInGrid().getX() * 4 + myConfig->getStartPositionInGrid().getY() * myMap->width * 4) + 2] = 0;
    myMap->FatImage[(myConfig->getStartPositionInGrid().getX() * 4 + myConfig->getStartPositionInGrid().getY() * myMap->width * 4) + 3] = 0.1;
    
    // Goal location
    myMap->FatImage[(myConfig->getGoalInGrid().getX() * 4 + myConfig->getGoalInGrid().getY() * myMap->width * 4) + 0] = 0;
    myMap->FatImage[(myConfig->getGoalInGrid().getX() * 4 + myConfig->getGoalInGrid().getY() * myMap->width * 4) + 1] = 255;
    myMap->FatImage[(myConfig->getGoalInGrid().getX() * 4 + myConfig->getGoalInGrid().getY() * myMap->width * 4) + 2] = 0;
    myMap->FatImage[(myConfig->getGoalInGrid().getX() * 4 + myConfig->getGoalInGrid().getY() * myMap->width * 4) + 3] = 0.1;
    
    // AStar
    for (std::list<Node*>::iterator listIterator = lstClearWaypointToDestination.begin(); listIterator != lstClearWaypointToDestination.end(); listIterator++)
    {
        int nX = (*listIterator)->getX() * myConfig->getGridMapResolution();
        int nY = (*listIterator)->getY() * myConfig->getGridMapResolution();
        myMap->FatImage[(nX * 4 + nY * myMap->width * 4) + 0] = 0;
        myMap->FatImage[(nX * 4 + nY * myMap->width * 4) + 1] = 255;
        myMap->FatImage[(nX * 4 + nY * myMap->width * 4) + 2] = 0;
        myMap->FatImage[(nX * 4 + nY * myMap->width * 4) + 3] = 0.1;
    }
    
    lodepng::encode("AStar.png", myMap->FatImage, myMap->width, myMap->height);
}
