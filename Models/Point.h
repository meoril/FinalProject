/*
 * Point.h
 *
 *  Created on: May 31, 2016
 *      Author: user
 */

#ifndef POINT_H_
#define POINT_H_

class Point {
public:
    Point();
    Point(double x, double y);
    virtual ~Point();
    double m_X;
    double m_Y;
    double getDistanceTo(Point *p);
    
    inline unsigned getX() {
        return m_X;
    };
    
    inline unsigned getY() {
        return m_Y;
    };
    
};

#endif /* POINT_H_ */
