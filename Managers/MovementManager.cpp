/*
 * MovementManager.cpp
 *
 *  Created on: Jun 11, 2016
 *      Author: colman
 */

#include "MovementManager.h"


MovementManager::MovementManager() {
	// TODO Auto-generated constructor stub

}

int MovementManager::moveToNextWatPoint(int nXdest, int nYdest, LocalizationManager *locManager)
{
	myrobot->Read();

	Position psCurrnt = locManager->getCurrentPosition();

	int nCurrX = psCurrnt.getX();
	int nCurrY = psCurrnt.getY();
	int nCurrYaw = psCurrnt.getYaw();

	//nCurrX = myrobot->getX();
	//nCurrY = myrobot->getY();

	cout << "x: " << nCurrX << ", y: " << nCurrY << endl;

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
		myrobot->setSpeed(LINEARSPEED, 0);

		//myrobot->Read();
		//nCurrX = myrobot->getX();
		//nCurrY = myrobot->getY();

		nCurrX = psCurrnt.getX();
		nCurrY = psCurrnt.getY();

		cout << "x: " << nCurrX << ", y: " << nCurrY << endl;
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

