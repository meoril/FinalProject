/*
 * Position.cpp
 *
 *  Created on: May 28, 2016
 *      Author: colman
 */

#include "Position.h"

Position::Position() {
	m_X = 0;
	m_Y = 0;
	m_Yaw = 0;
}

Position::Position(double x, double y, double yaw) {
	m_X = x;
	m_Y = y;
	m_Yaw = yaw;
}

Position::~Position() {
}

