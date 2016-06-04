/*
 * Size.h
 *
 *  Created on: May 28, 2016
 *      Author: colman
 */
#ifndef SIZE_H_
#define SIZE_H_
#include <algorithm>

class Size {
public:
    Size();
    Size(float height, float width);
    virtual ~Size();
    float m_Height;
    float m_Width;
    float RadiosSize();
};
#endif
