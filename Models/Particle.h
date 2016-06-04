/*
 * Particle.h
 *
 *  Created on: May 31, 2016
 *      Author: user
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

class Particle {
private:
	double m_xPos, m_yPos, m_yaw, m_belief;

public:
	Particle(double xPos, double yPos, double yaw);
	double getBelief();
	void Update(double deltaX, double deltaY, double deltaYaw, float moveScan, float laserScan);
	Particle* CreateChild();
	~Particle();
};

#endif /* PARTICLE_H_ */
