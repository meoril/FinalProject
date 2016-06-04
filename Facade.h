/*
 * Facade.h
 *
 *  Created on: May 31, 2016
 *      Author: colman
 */

#ifndef FACADE_H_
#define FACADE_H_
#include "Models/Map.h"
#include "Managers/ConfigurationManager.h"
class Facade {
public:
    Facade();
    virtual ~Facade();
    void Run();
private:
    Map* myMap;
    ConfigurationManager* config;
};

#endif /* FACADE_H_ */
