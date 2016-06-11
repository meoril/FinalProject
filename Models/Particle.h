/*
 * Particle.h
 *
 *  Created on: May 31, 2016
 *      Author: user
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_
#include "Position.h"
#include "Map.h"
#include <libplayerc++/playerc++.h>
using namespace PlayerCc;

class Particle {
private:
	Position m_pos;

public:
	Particle(double xPos, double yPos, double yaw);
	float getBelief();
	void Update(double deltaX, double deltaY, double deltaYaw, const Map* map, const LaserProxy* laser);
	Particle* CreateChild(const int expansionRadius, const int yawRange);
	~Particle();
	Position getPosition();
	float m_belief;
	unsigned m_age;

};

#endif /* PARTICLE_H_ */
