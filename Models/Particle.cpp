/*
 * Particle.cpp
 *
 *  Created on: May 31, 2016
 *      Author: user
 */

#include "Particle.h"
#include <iostream>
using namespace std;

Particle::Particle(double xPos, double yPos, double yaw){

}
	double Particle::getBelief(){
		return 0;
	}
	void Particle::Update(double deltaX, double deltaY, double deltaYaw, float moveScan, float laserScan){

	}
	Particle* Particle::CreateChild()
	{
		return NULL;
	}
	Particle::~Particle()
	{

	}
