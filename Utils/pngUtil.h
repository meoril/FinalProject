/*
 * pngUtil.h
 *
*
 *      Authors: Meori Lehr, 204079503
 *      Ziv Oren, 305464166
 *      Noa Tsror, 305427114
 */

#ifndef PNGUTIL_H_
#define PNGUTIL_H_
#include <iostream>
#include <vector>

void encodeOneStep(const char* filename, std::vector<unsigned char> image, unsigned width, unsigned height);
void decodeOneStep(const char* filename);
void InflateMap(const char* filename, double resolution, int robotWidth, int robotHeight);



#endif /* PNGUTIL_H_ */
