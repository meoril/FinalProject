/*
 * Size.cpp
 *
 *  Created on: May 28, 2016
 *      Author: colman
 */

#include "Size.h"
using namespace std;

Size::Size() {
	m_Height = 0;
	m_Width =0;
}

Size::Size(float height, float width){
	m_Height = height;
	m_Width = width;
}

Size::~Size() {
}

float Size::RadiosSize(){
	return std::max(m_Height, m_Width);
}

