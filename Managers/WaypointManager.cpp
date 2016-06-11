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


int WaypointManager::createWayPoints(std::list<Node*> lstinPath, std::list<Node*> lstoutWayPoints)
{
	int nNumOfWayPoints = 0;
	int nCurrDegree;
	int nNextDegree;

	// Get three points from the list
	std::list<Node*>::iterator next = lstinPath.begin();
	Node* prev = (Node*)(*next);
	next++;
	Node* curr = (Node*)(*next);
	next++;

	lstoutWayPoints.push_front(prev);

	if(next == lstinPath.end())
	{
		cout << "The path is too short" << endl;
	}
	else
	{
		// Going over the A star Path
		while (next != lstinPath.end())
		{
			// Getting the degree between the two next parts in the path
			nCurrDegree = BaseUtils::DegreeBetweenPoints(prev->getX(), prev->getY(), curr->getX(), curr->getY());
			nNextDegree = BaseUtils::DegreeBetweenPoints(curr->getX(), curr->getY(), ((Node*)(*next))->getX(), ((Node*)(*next))->getY());

			// If the robot changed his degree, add the point into way points, if
			// the robot is in the same direction, the point would not be in the way points
			if (nCurrDegree != nNextDegree)
			{
				lstoutWayPoints.push_back(curr);
				nNumOfWayPoints++;
			}

			// Keep on moving on the list
			prev = curr;
			curr = (Node*)(*next);
			next++;
		}

		cout << nNumOfWayPoints << " way points created" << endl;
	}

	return nNumOfWayPoints;
}


} /* namespace Managers */
