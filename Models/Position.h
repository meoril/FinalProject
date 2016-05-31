/*
 * Position.h
 *
 *  Created on: May 28, 2016
 *      Author: colman
 */


class Position {
public:
	Position();
	Position(double x, double y, double Yaw);
	virtual ~Position();
	double m_X;
	double m_Y;
	double m_Yaw;


	inline unsigned getX() {
		return m_X;
	};

	inline unsigned getY() {
		return m_Y;
	};

	inline unsigned getYaw() {
		return m_Yaw;
	};

};
