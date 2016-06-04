/*
 * LocalizationManager.cpp
 *
 *  Created on: May 31, 2016
 *      Author: user
 */


#include "LocalizationManager.h"

using namespace PlayerCc;
using namespace std;

LocalizationManager::LocalizationManager(Map* map, LaserProxy* laser){
	this->_map = map;
	this->_laser = laser;
}

void LocalizationManager::update(double deltaX, double deltaY, double deltaYaw){
	for (vector<Particle*>::iterator it = this->_particles.begin() ; it != this->_particles.end(); ++it){
		(*it)->Update(deltaX,deltaY,deltaYaw, this->_map, this->_laser);
		(*it)->m_age +=1;
	}
}

Particle* LocalizationManager::getBestParticle(){
	Particle* bestParticle = _particles[0];

	// Looking for highest belief
	for (unsigned index=1;index<this->_particles.size();index++){
		if(this->_particles[index]->m_belief > bestParticle->m_belief){
			bestParticle = _particles[index];
		}
	}

	return bestParticle;
}
LocalizationManager::~LocalizationManager(){

}


