/*
 * LocalizationManager.h
 *
 *  Created on: May 31, 2016
 *      Author: user
 */

#ifndef LOCALIZATIONMANAGER_H_
#define LOCALIZATIONMANAGER_H_
#include "../Models/Map.h"
#include "../Models/Particle.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <libplayerc++/playerc++.h>
using namespace PlayerCc;
using namespace std;

namespace Managers {

class LocalizationManager {

private:
	vector<Particle *> _particles;

public:
	LocalizationManager(Map* map, LaserProxy* laser, Position* start);

	// Gets changes in position and updates the particles accordingly
	void update(double deltaX, double deltaY, double deltaYaw);
	Particle *getBestParticle();
	virtual ~LocalizationManager();

	// Get the current position according to particle belief (Uses getBestParticle)
	Position getCurrentPosition();

	static const float MAGIC_NUM = 1.2;
	static const int GOOD_BREED = 16;
	static const int NORMAL_BREED = 5;

private:
	void BreedParticle(Particle* particle, int numToBreed, vector<Particle*>*  children);
	Map* _map;
	LaserProxy* _laser;

};
}
#endif /* LOCALIZATIONMANAGER_H_ */
