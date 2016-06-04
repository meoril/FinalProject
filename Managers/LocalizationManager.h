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
using namespace std;

#include <libplayerc++/playerc++.h>
using namespace PlayerCc;
namespace Managers {

class LocalizationManager {

private:
	vector<Particle *> _particles;

public:
	LocalizationManager();
	void update(double deltaX, double deltaY, double deltaYaw);
	void resampleParticles();
	Particle *getBestParticle();
	virtual ~LocalizationManager();
};

#endif /* LOCALIZATIONMANAGER_H_ */
