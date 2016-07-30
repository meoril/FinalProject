/*
 * MovementManager.cpp
 *
 *  Created on: Jun 11, 2016
 *      Author: colman
 */

#include "MovementManager.h"


MovementManager::MovementManager(Robot* myinRobot) {
    
    myrobot = myinRobot;
    
    myrobot->Read();
    myrobot->setOdometry(myrobot->robotStartPosition.getX(), myrobot->robotStartPosition.getY(), myrobot->robotStartPosition.getYaw());
}

int MovementManager::moveToNextWatPoint(int nXdest, int nYdest, LocalizationManager *locManager)
{
    myrobot->Read();
    
    Position psCurrnt = locManager->getCurrentPosition();
    
    int nCurrX = psCurrnt.getX();
    int nCurrY = psCurrnt.getY();
    int nCurrYaw = psCurrnt.getYaw();
    
    int nRobCurrX = myrobot->getX();
    int nRobCurrY = myrobot->getY();
    int nRobCurrYaw = myrobot->getYaw();
    
    // Debug prints
    cout << "x: " << nCurrX << ", y: " << nCurrY << endl;
    cout << "x rob: " << nRobCurrX << ", y rob: " << nRobCurrY << endl;
    cout << BaseUtils::DegreeToRadian(BaseUtils::DegreeBetweenPoints(nCurrX, nCurrY, nXdest, nYdest))
    << "  " << BaseUtils::DegreeToRadian(nCurrYaw) << endl;
    cout << abs(BaseUtils::DegreeToRadian(BaseUtils::DegreeBetweenPoints(nCurrX, nCurrY, nXdest, nYdest))
                - BaseUtils::DegreeToRadian(nCurrYaw)) <<  " "<< DEGREETOLERANCE <<endl;
    
    // Turn to the right direcation
    while (abs(BaseUtils::DegreeToRadian(BaseUtils::DegreeBetweenPoints(nCurrX, nCurrY, nXdest, nYdest))
               - BaseUtils::DegreeToRadian(nCurrYaw)) > 0.15)
    {
        myrobot->Read();
        
        myrobot->setSpeed(0, 0.1);
        
        myrobot->Read();
        myrobot->Read();
        myrobot->Read();
        myrobot->Read();
        myrobot->Read();
        
        cout << abs(BaseUtils::DegreeToRadian(BaseUtils::DegreeBetweenPoints(nCurrX, nCurrY, nXdest, nYdest))
                    - BaseUtils::DegreeToRadian(nCurrYaw)) <<  " "<< DEGREETOLERANCE <<endl;
        
        //nCurrYaw = psCurrnt.getYaw();
        nCurrYaw = myrobot->getYaw();
    }
    
    // Move fast
    while (BaseUtils::Distance(nCurrX, nCurrY, nXdest, nYdest) > SLOWSPEEDRANGE)
    {
        myrobot->Read();
        
        //myrobot->setSpeed(LINEARSPEED, 0);
        myrobot->setSpeed(1, 0);
        
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
        
        nCurrX = myrobot->getX();
        nCurrY = myrobot->getY();
        
        cout << "x: " << nCurrX << ", y: " << nCurrY << endl;
        //cout << "x rob: " << nRobCurrX << ", y rob: " << nRobCurrY << endl;
        cout << "Distance "<< BaseUtils::Distance(nCurrX, nCurrY, nXdest, nYdest) << SLOWSPEEDRANGE << endl;
    }
    
    // Move slow to get to the waypoint
    while (BaseUtils::Distance(nCurrX, nCurrY, nXdest, nYdest) > TOLERANCE)
    {
        myrobot->setSpeed(LINEARSPEED * SLOWSPEEDRATIO, 0);
        
        for (int n = 0; n <20; n++)
        {
            myrobot->Read();
        }
        nCurrX = myrobot->getX();
        nCurrY = myrobot->getY();
        
        cout << "x: " << nCurrX << ", y: " << nCurrY << endl;
    }
    
    myrobot->setSpeed(0, 0);
    
    return nCurrYaw;
    
}

MovementManager::~MovementManager() {
    // TODO Auto-generated destructor stub
}

