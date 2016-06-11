/*
 * WaypointManager.h
 *
 *  Created on: Jun 4, 2016
 *      Author: colman
 */

#ifndef WAYPOINTMANAGER_H_
#define WAYPOINTMANAGER_H_
#include "../Models/Node.h"
#include "../Models/Robot.h"
#include "../Utils/BaseUtils.h"

namespace Managers {

class WaypointManager {
public:
	WaypointManager();
	virtual ~WaypointManager();

	bool isInWaypointRange(Node* nWaypoint);
	// TODO: init nIsInRange in Facade
	int nIsInRange;
	int createWayPoints(std::list<Node*> lstinPath, std::list<Node*> lstoutWayPoints);


private:
	Robot *robot;

};

} /* namespace Managers */

#endif /* WAYPOINTMANAGER_H_ */

