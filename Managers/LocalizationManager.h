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
#include "../Utils/BaseUtils.h"
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
	LocalizationManager(Map* map, LaserProxy* laser);
	void update(double deltaX, double deltaY, double deltaYaw);
	Particle *getBestParticle();
	virtual ~LocalizationManager();
	static const float MAGIC_NUM = 1.2;

private:
	Map* _map;
	LaserProxy* _laser;
};

#endif /* LOCALIZATIONMANAGER_H_ */
