/*
 * LocalizationManager.cpp
 *
 *  Created on: May 31, 2016
 *      Author: Ziv Oren
 */

#include "LocalizationManager.h"
#include "../Utils/BaseUtils.h"
using namespace PlayerCc;
using namespace std;

LocalizationManager::LocalizationManager(Map* map, LaserProxy* laser, Position* start){
	this->_map = map;
	this->_laser = laser;

	// Creating first particle
	this->_particles.push_back(new Particle(start->getX(),start->getY(),start->getYaw()));
}

void LocalizationManager::BreedParticle(Particle* particle, int numToBreed, vector<Particle*>*  children){

	// Getting how much particles to create
	int numToCreate = std::min((int)(BaseUtils::PARTICLES_NUMBER - this->_particles.size() - children->size()), (int)numToBreed);

	// Creating particles
	for (int i = 0; i<numToCreate; i++) {
		children->push_back(particle->CreateChild(10,1));
	}
}

void LocalizationManager::update(double deltaX, double deltaY, double deltaYaw){
	vector<Particle*> toAdd;
	vector<int> toRemove;

	// Updating particles
	for (unsigned int index = 0 ; index < this->_particles.size(); ++index){
		Particle* particle = _particles[index];

		particle->Update(deltaX,deltaY,deltaYaw, this->_map, this->_laser);
		particle->m_age +=1;

		float belief = particle->getBelief();
		if (belief <= BaseUtils::MIN_BELIEF_THRESHOLD){
			toRemove.push_back(index);

		}
		else if (belief >= BaseUtils::GOOD_BELIEF_THRESHOLD){
			BreedParticle(particle, GOOD_BREED , &toAdd);
		}
		else {
			BreedParticle(particle,NORMAL_BREED, &toAdd);
		}
	}

	// Removing unwanted children
	for (int index = toRemove.size()-1; index>=0;--index){
		Particle* partToRem = _particles[toRemove[index]];
		_particles.erase(_particles.begin()+toRemove[index]);
		delete partToRem;
	}

	// Pushing children
	for (vector<Particle*>::iterator it = toAdd.begin(); it != toAdd.end(); ++it){
		this->_particles.push_back(*it);
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

Position LocalizationManager::getCurrentPosition(){
	return this->getBestParticle()->getPosition();
}

LocalizationManager::~LocalizationManager(){
	// Deletes all particles
	for (vector<Particle*>::iterator it = this->_particles.begin() ; it != this->_particles.end(); ++it){
		delete *it;
	}
}
