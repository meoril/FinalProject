/*
 * Facade.h
 *
 *  Created on: May 31, 2016
 *      Author: colman
 */

#ifndef FACADE_H_
#define FACADE_H_
#include "Models/Map.h"
#include "Models/Point.h"
#include "Models/Robot.h"
#include "Utils/PathPlanner.h"
#include "Managers/ConfigurationManager.h"
#include "Models/Robot.h"
class Facade {
public:
    Facade();
    virtual ~Facade();
    void Run();
private:
    Map* myMap;
    ConfigurationManager* myConfig;
    Robot* myRobot;
};

#endif /* FACADE_H_ */
