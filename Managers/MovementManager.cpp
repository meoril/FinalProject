/*
 * MovementManager.cpp
 *
 *  Created on: Jun 11, 2016
 *      Author: colman
 */

#include "MovementManager.h"


MovementManager::MovementManager(Robot* myinRobot) {

	myrobot = myinRobot;


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

	cout << "x: " << nCurrX << ", y: " << nCurrY << endl;
	cout << "x rob: " << nRobCurrX << ", y rob: " << nRobCurrY << endl;

	// Turn to the right direcation
	while (BaseUtils::DegreeToRadian(BaseUtils::DegreeBetweenPoints(nCurrX, nCurrY, nXdest, nYdest))
			- nCurrYaw > DEGREETOLERANCE)
	{
		myrobot->setSpeed(0, YAWSPEED);

		nCurrYaw = psCurrnt.getYaw();
	}

	// Move fast
	while (BaseUtils::Distance(nCurrX, nCurrY, nXdest, nYdest) > SLOWSPEEDRANGE)
	{
		myrobot->Read();
		myrobot->Read();
		//myrobot->setSpeed(LINEARSPEED, 0);
		myrobot->setSpeed(2, 0);

		nRobCurrX = myrobot->getX();
		nRobCurrY = myrobot->getY();

		locManager->update(nRobCurrX - nCurrX, nRobCurrY - nCurrY, nRobCurrYaw - nCurrYaw);
		psCurrnt = locManager->getCurrentPosition();

		nCurrX = psCurrnt.getX();
		nCurrY = psCurrnt.getY();

		cout << "x: " << nCurrX << ", y: " << nCurrY << endl;
		cout << "x rob: " << nRobCurrX << ", y rob: " << nRobCurrY << endl;
	}

	// Move slow to get to the waypoint
	while (BaseUtils::Distance(nCurrX, nCurrY, nXdest, nYdest) > TOLERANCE)
	{
		myrobot->setSpeed(LINEARSPEED * SLOWSPEEDRATIO, 0);

		myrobot->Read();
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

