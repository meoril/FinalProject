/*
 * Position.h
 *
 *  Created on: May 28, 2016
 *      Author: colman
 */
#include "Point.h"

class Position {
public:
	Position();
	Position(double x, double y, double Yaw);
	virtual ~Position();
	void setX(double x);
	void setY(double y);
	void setYaw(double yaw);

	Point m_Pnt;
	double m_Yaw;
	inline unsigned getX() {
		return m_Pnt.m_X;
	};

	inline unsigned getY() {
		return m_Pnt.m_Y;
	};

	inline unsigned getYaw() {
		return m_Yaw;
	};

};