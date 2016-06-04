* Facade.cpp

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
}
