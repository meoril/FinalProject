/*
 * Facade.cpp
 *
 *  Created on: May 31, 2016
 *      Author: colman
 */

#include "Facade.h"
#include <string>
#include <sstream>

Facade::Facade()
{
    myConfig = new ConfigurationManager("Resources/parameters.txt");
    myMap = new Map(myConfig);
    myRobot = new Robot("10.10.245.63", 6665, myConfig->getStartPosition(), myConfig->getGoal(), myConfig->getRobotSize(), true);
    //myRobot = new Robot("127.0.0.1", 6665, myConfig->getStartPosition(), myConfig->getGoal(), myConfig->getRobotSize(), true);

    for (int i=0;i <10;i++) {
    	myRobot->Read();
    }

    //LaserProxy* lsProxy;
    locManager = new LocalizationManager(myMap, myRobot->getLaserProxy(), new Position(
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
    std::list<Node*> lstRealLoc;

    for (std::list<Node*>::iterator listIterator = lstPath.begin();
         listIterator != lstPath.end(); listIterator++)
    {
        Node* nCurr = *listIterator;
        int nCurrX = nCurr->getX() * myConfig->getGridMapResolution();
        int nCurrY = nCurr->getY() * myConfig->getGridMapResolution();

        Node *nConvertedNode = new Node(nCurrX, nCurrY, true, NULL);
        lstMapPath.push_back(nConvertedNode);
    }

    //cout << lstPath.size() << endl;
    std::list<Node*> lstWayPoints;
    WaypointManager* mngWayPoint = new WaypointManager();
    mngWayPoint->createWayPoints(lstMapPath, &lstWayPoints);

    //this->printPath(lstWayPoints, "CleanPath.png");
    Particle* best;
    int i = 1;

    for (std::list<Node*>::iterator listIterator = lstWayPoints.begin();
         listIterator != lstWayPoints.end() ;listIterator++)
    {
        Node* nCurr = *listIterator;
        int nCurrYaw = moveManager->moveToNextWatPoint(nCurr->getPoint(),
                                                       locManager);

        best = locManager->getBestParticle();


        cout << "Best particle: x - " << best->getPosition().getX() << "  y - " << best->getPosition().getX() << endl
    			 << "Current position: x - " << myRobot->getX() << " y - " << myRobot->getY() << endl << endl;

        //lstRealLoc.push_back(new Node(, true, NULL));
        std::list<Node*> locNode;
        locNode.push_back(new Node(myRobot->getX(), myRobot->getY(), myRobot->getYaw(), NULL));
        std::stringstream sstm;
        sstm << "RealLoc" << i << ".png";
        this->printPath(locNode, sstm.str());
        i++;
    }
}

void Facade::printPath(std::list<Node*>& lstStarPath, std::string name){

    Position startPoint = myConfig->getStartPositionInGrid();
    Position bla = myConfig->getStartPosition();
    int nStartPoint = (myConfig->getStartPositionInGrid().getX() * 4 + myConfig->getStartPositionInGrid().getY() * myMap->width * 4);
    // Start location
    myMap->RegImage[nStartPoint + 0] = 255;//255
    myMap->RegImage[nStartPoint + 1] = 0;
    myMap->RegImage[nStartPoint + 2] = 0;
    myMap->RegImage[nStartPoint + 3] = 0.1;
    
    Point goalPoint = myConfig->getGoalInGrid();
    Point stam = myConfig->getGoal();
    int nGoalPoint = (myConfig->getGoalInGrid().getX() * 4 + myConfig->getGoalInGrid().getY() * myMap->width * 4);
    // Goal location
    myMap->RegImage[nGoalPoint + 0] = 0;
    myMap->RegImage[nGoalPoint + 1] = 255;//255
    myMap->RegImage[nGoalPoint + 2] = 0;
    myMap->RegImage[nGoalPoint + 3] = 0.1;
    
    // AStar
    for (std::list<Node*>::iterator listIterator = lstStarPath.begin(); listIterator != lstStarPath.end(); listIterator++)
    {
        int nX = (*listIterator)->getX();// * myConfig->getGridMapResolution();
        int nY = (*listIterator)->getY();// * myConfig->getGridMapResolution();
        int nPoint = (nX * 4 + nY * myMap->width * 4);
        myMap->RegImage[nPoint + 0] = 124;
        myMap->RegImage[nPoint + 1] = 252;//255
        myMap->RegImage[nPoint + 2] = 0;
        myMap->RegImage[nPoint + 3] = 0;
    }
    
    lodepng::encode(name, myMap->RegImage, myMap->width, myMap->height);
}
