/*
 * Facade.h
 *
 *  Created on: May 31, 2016
 *      Author: colman
 */

#ifndef FACADE_H_
#define FACADE_H_
#include "Models/Map.h"
class Facade {
public:
	Facade();
	virtual ~Facade();
	void Run();
private:
	Map* myMap;
};

#endif /* FACADE_H_ */
