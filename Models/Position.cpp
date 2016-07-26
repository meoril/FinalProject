/*
 * Position.cpp
 *
 *  Created on: May 28, 2016
 *      Author: colman
 */

#include "Position.h"

Position::Position()
:m_Pnt()
{
    m_Yaw = 0;
}

Position::Position(double x, double y, double yaw)
:m_Pnt(x,y)
{
    m_Yaw = yaw;
}

void Position::setX(double x){
    this->m_Pnt.m_X = x;
}

void Position::setY(double y){
    this->m_Pnt.m_Y = y;
}

void Position::setYaw(double yaw){
    this->m_Yaw = yaw;
}

Position::~Position() {
}

