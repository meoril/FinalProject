/*
 * MovementManager.cpp
 *
 *  Created on: Jun 11, 2016
 *      Author: colman
 */

#include "MovementManager.h"

Position Update(int deltaX, int deltaY, int deltaYaw, LocalizationManager* locManager){
	locManager->update(deltaX,deltaY,deltaYaw);
	return locManager->getCurrentPosition();
}

MovementManager::MovementManager(Robot* myinRobot) {

    myrobot = myinRobot;

    myrobot->Read();
    myrobot->setOdometry(myrobot->robotStartPosition.getX(), myrobot->robotStartPosition.getY(), myrobot->robotStartPosition.getYaw());
}

int MovementManager::moveToNextWatPoint(Point *pDest, LocalizationManager *locManager)
{
    myrobot->Read();

    Position pCurrPos = locManager->getCurrentPosition();

    //Position *pCurrPos = new Position(psCurrnt.getX(), psCurrnt.getY(), psCurrnt.getYaw());
    //	int nCurrX = psCurrnt.getX();
    //	int nCurrY = psCurrnt.getY();
    //	int nCurrYaw = psCurrnt.getYaw();

    //int nRobCurrX = myrobot->getX();
    //int nRobCurrY = myrobot->getY();
    //	nCurrX = myrobot->getX();
    //	nCurrY = myrobot->getY();
    //	int nRobCurrYaw = myrobot->getYaw();

    double degreeBetweenThePoints = BaseUtils::DegreeToRadian(BaseUtils::DegreeBetweenPoints(pCurrPos.m_Pnt, *pDest));
    double degreesDiff = degreeBetweenThePoints - BaseUtils::DegreeToRadian(pCurrPos.getYaw());
    cout << "yaw diff between points: " << degreesDiff << endl;

    cout << "curr robot yaw: " << pCurrPos.getYaw() << endl;
    // Turn to the right direcation
    while (abs(degreesDiff) > 0.13)
    {
        myrobot->Read();

        if (degreesDiff > 0){
            myrobot->setSpeed(0, 0.1);
        }
        else{
            myrobot->setSpeed(0, -0.1);
        }

        myrobot->Read();
        myrobot->Read();
        myrobot->Read();
        myrobot->Read();
        myrobot->Read();

        pCurrPos = Update(0,0,myrobot->getYaw()-pCurrPos.getYaw(),locManager);

        degreesDiff = degreeBetweenThePoints - BaseUtils::DegreeToRadian(pCurrPos.getYaw());
        cout << "curr yaw: " << BaseUtils::DegreeToRadian(pCurrPos.getYaw()) << endl;
        cout << "curr degree diff: " << degreesDiff << endl;
    }

    int currTolerance = TOLERANCE;

    cout << "Distance from end goal and this goal: " << pCurrPos.m_Pnt.getDistanceTo(&myrobot->robotGoal) << endl;
    if (pDest->getDistanceTo(&myrobot->robotGoal) < 5){
        currTolerance /= 3;
    }

    // Move fast
    while (pCurrPos.m_Pnt.getDistanceTo(pDest) > currTolerance * 1.5)
    {
        myrobot->Read();

        myrobot->setSpeed(0.5, 0);

        myrobot->Read();
        myrobot->Read();
        myrobot->Read();
        myrobot->Read();
        myrobot->Read();

        //nRobCurrX = myrobot->getX();
        //nRobCurrY = myrobot->getY();
        //locManager->update(nRobCurrX - nCurrX, nRobCurrY - nCurrY, nRobCurrYaw - nCurrYaw);
        //psCurrnt = locManager->getCurrentPosition();
        //nCurrX = psCurrnt.getX();
        //nCurrY = psCurrnt.getY();

        pCurrPos = Update(myrobot->getX()-pCurrPos.getX(),myrobot->getY()-pCurrPos.getY(), myrobot->getYaw()-pCurrPos.getYaw(), locManager);


        cout << "destx: " << pDest->getX() << ", desty: " << pDest->getY() << endl;
        cout << "currx: " << pCurrPos.getX() << ", curry: " << pCurrPos.getY() << endl;
        cout << "distance: " << pCurrPos.m_Pnt.getDistanceTo(pDest) << endl;
    }

    // Move slow to get to the waypoint
    while (pCurrPos.m_Pnt.getDistanceTo(pDest) > currTolerance)
    {
        myrobot->setSpeed(LINEARSPEED * SLOWSPEEDRATIO, 0);

        for (int n = 0; n <20; n++)
        {
            myrobot->Read();
        }
        pCurrPos = Update(myrobot->getX()-pCurrPos.getX(),myrobot->getY()-pCurrPos.getY(), myrobot->getYaw()-pCurrPos.getYaw(), locManager);
        cout << "x: " << pCurrPos.getX() << ", y: " << pCurrPos.getY() << endl;
    }

    myrobot->setSpeed(0, 0);

    cout << "got to waypoint: x-" << pDest->getX() << ", y-" << pDest->getY() << endl;
    return pCurrPos.getYaw();

}

MovementManager::~MovementManager() {
    // TODO Auto-generated destructor stub
}

