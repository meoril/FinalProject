/*
 * Point.cpp
 *
 *  Created on: May 31, 2016
 *      Author: user
 */
#include <math.h>

using namespace std;
#include "Point.h"

Point::Point() {
    this->m_X =0;
    this->m_Y = 0;
    
}

Point::Point(double x, double y) {
    this->m_X = x;
    this->m_Y = y;
    
}

Point::~Point() {
    
}

double Point::getDistanceTo(Point *p)
{
    return sqrt(pow((this->getX() - p->getX()), 2) + pow((this->getY() - p->getY()), 2));
}

