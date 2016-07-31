/*
 * Facade.cpp
 *
 *  Created on: May 31, 2016
 *      Author: colman
 */

#include "Facade.h"

Facade::Facade()
{
    myConfig = new ConfigurationManager("Resources/parameters.txt");
    myMap = new Map(myConfig);
    myRobot = new Robot("127.0.0.1", 6665, myConfig->getStartPosition(), myConfig->getGoal(), myConfig->getRobotSize(), true);
    
    LaserProxy* lsProxy;
    locManager = new LocalizationManager(myMap, lsProxy, new Position(
                                                                      myRobot->getX(), myRobot->getY(), myRobot->getYaw()));
    
    moveManager = new MovementManager(myRobot);
}

Facade::~Facade() {
    delete myConfig;
    delete myMap;
    delete myRobot;
    delete locManager;
    delete moveManager;
    
}

void Facade::Run()
{
    PathPlanner* pathPlanner = new PathPlanner();
    Point* tempStartPoint = new Point(myConfig->getStartPositionInGrid().getX(), myConfig->getStartPositionInGrid().getY());
    std::list<Node*> lstPath = pathPlanner->AStarPath(*tempStartPoint, myConfig->getGoalInGrid(), myMap);
    
    std::list<Node*> lstMapPath;
    
    for (std::list<Node*>::iterator listIterator = lstPath.begin();
         listIterator != lstPath.end(); listIterator++)
    {
        Node* nCurr = *listIterator;
        int nCurrX = nCurr->getX() * myConfig->getGridMapResolution();
        int nCurrY = nCurr->getY() * myConfig->getGridMapResolution();
        
        Node *nConvertedNode = new Node(nCurrX, nCurrY, true, NULL);
        lstMapPath.push_back(nConvertedNode);
    }
    
    cout << lstPath.size() << endl;
    std::list<Node*> lstWayPoints;
    WaypointManager* mngWayPoint = new WaypointManager();
    mngWayPoint->createWayPoints(lstMapPath, &lstWayPoints);
    
    this->printPath(lstWayPoints, "CleanPath.png");
    Particle* best;
    
    for (std::list<Node*>::iterator listIterator = lstWayPoints.begin();
         listIterator != lstWayPoints.end() ;listIterator++)
    {
        Node* nCurr = *listIterator;
        int nCurrYaw = moveManager->moveToNextWatPoint(nCurr->getPoint(),
                                                       locManager);
        
        best = locManager->getBestParticle();
        
        //    		locManager->update(best->getPosition().getX() - nCurr->getX(),
        //    						   best->getPosition().getY() - nCurr->getY(),
        //    						   best->getPosition().getYaw() - nCurrYaw);
        
        
        cout << "Best particle: x - " << best->getPosition().getX() << "  y - " << best->getPosition().getX() << endl
    			 << "Current position: x - " << myRobot->getX() << " y - " << myRobot->getY() << endl << endl;
        
    }
}

void Facade::printPath(std::list<Node*>& lstStarPath, std::string name){
    
    Position startPoint = myConfig->getStartPositionInGrid();
    Position bla = myConfig->getStartPosition();
    int nStartPoint = (myConfig->getStartPositionInGrid().getX() * 4 + myConfig->getStartPositionInGrid().getY() * myMap->width * 4);
    // Start location
    myMap->FatImage[nStartPoint + 0] = 255;//255
    myMap->FatImage[nStartPoint + 1] = 0;
    myMap->FatImage[nStartPoint + 2] = 0;
    myMap->FatImage[nStartPoint + 3] = 0.1;
    
    Point goalPoint = myConfig->getGoalInGrid();
    Point stam = myConfig->getGoal();
    int nGoalPoint = (myConfig->getGoalInGrid().getX() * 4 + myConfig->getGoalInGrid().getY() * myMap->width * 4);
    // Goal location
    myMap->FatImage[nGoalPoint + 0] = 0;
    myMap->FatImage[nGoalPoint + 1] = 255;//255
    myMap->FatImage[nGoalPoint + 2] = 0;
    myMap->FatImage[nGoalPoint + 3] = 0.1;
    
    // AStar
    for (std::list<Node*>::iterator listIterator = lstStarPath.begin(); listIterator != lstStarPath.end(); listIterator++)
    {
        int nX = (*listIterator)->getX();// * myConfig->getGridMapResolution();
        int nY = (*listIterator)->getY();// * myConfig->getGridMapResolution();
        int nPoint = (nX * 4 + nY * myMap->width * 4);
        myMap->FatImage[nPoint + 0] = 0;
        myMap->FatImage[nPoint + 1] = 255;//255
        myMap->FatImage[nPoint + 2] = 0;
        myMap->FatImage[nPoint + 3] = 0.1;
    }
    
    lodepng::encode(name, myMap->FatImage, myMap->width, myMap->height);
}
