/*
 * Facade.cpp
 *
 *  Created on: May 31, 2016
 *      Author: colman
 */

#include "Facade.h"

Facade::Facade() {
    config = new ConfigurationManager("Resources/Parameters.txt");
    myMap = new Map(config);
}

Facade::~Facade() {
}

void Facade::Run(){
    
}
