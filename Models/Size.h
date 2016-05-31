/*
 * Size.h
 *
 *  Created on: May 28, 2016
 *      Author: colman
 */
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
