/*
 * WaypointManager.cpp
 *
 *  Created on: Jun 4, 2016
 *      Author: colman
 */

#include "WaypointManager.h"

namespace Managers {

WaypointManager::WaypointManager() {
	// TODO Auto-generated constructor stub

}

WaypointManager::~WaypointManager() {
	// TODO Auto-generated destructor stub
}

bool WaypointManager::isInWaypointRange(Node* nWaypoint)
{
	bool bIsInRange = false;

	int nXdiff = abs(this->robot->getMatrixX() - nWaypoint->getX());
	int nYdiff = abs(this->robot->getMatrixY() - nWaypoint->getY());

	if ((nXdiff < nIsInRange) && (nYdiff < nIsInRange))
	{
		bIsInRange = true;
	}

	cout << nXdiff << ":" << nYdiff << endl;
	return (bIsInRange);
}


} /* namespace Managers */
