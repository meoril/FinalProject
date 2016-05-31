/*
 * pngUtil.cpp
 *
 *      Authors: Meori Lehr, 204079503
 *      Ziv Oren, 305464166
 *      Noa Tsror, 305427114
 */

#include "pngUtil.h"
#include "lodepng.h"
#include <stdio.h>
#include <math.h>
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;
using namespace lodepng;
//Encode from raw pixels to disk with a single function call
//The image argument has width * height RGBA pixels or width * height * 4 bytes
void encodeOneStep(const char* filename, vector<unsigned char> image,
		unsigned width, unsigned height) {
	//Encode the image
	unsigned error = encode(filename, image, width, height);

	//if there's an error, display it
	if (error)
		cout << "encoder error " << error << ": "
				<< lodepng_error_text(error) << endl;
}

void decodeOneStep(const char* filename) {
	vector<unsigned char> image;
	unsigned width, height;

	//decode the image
	unsigned error = decode(image, width, height, filename);

	// check if an error occurred
	if (error)
		// Print the error
		cout << "decoder error " << error << ": "
				<< lodepng_error_text(error) << endl;

	//the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA..., use it as texture, draw it, ...
}

void InflateMap(const char* filename, double resolution, int robotWidth, int robotHeight) {
	std::vector<unsigned char> image;
	unsigned width, height;
	unsigned robotStep;
	double robotRadius;
	vector<unsigned char> inflatedImage;
	inflatedImage.resize(width * height *4);

	// Calculate the robot radius
	robotRadius = max(robotHeight, robotWidth) / 2;

	// Decode map from the origin file
	unsigned error = decode(image, width, height, filename);

	// Check if an error occurred while decoding
	if (error)
		// Print the error
		cout << "decoder error " << error << ": "
				<< lodepng_error_text(error) << endl;

	// Paint the new map image in white
	for(unsigned int i = 0; i < width*height*4; i++)
	{
		inflatedImage[i] = image[i];
	}


	for (unsigned int i = 0; i < height; i++)
		for (unsigned int j = 0; j < width; j++) {
			if ((image[i * width * 4 + j * 4 + 0] == 0) &&
			    (image[i * width * 4 + j * 4 + 1] == 0) &&
				(image[i * width * 4 + j * 4 + 2] == 0))
			{
				robotStep = ceil(robotRadius/resolution);

				for(unsigned int x =i-robotStep; x<=i+robotStep;x++)
				{
					// check if still in x axis bounding
					if (x >= 0 && x < height)
					{
						for (unsigned int y=j-robotStep; y<=j+robotStep; y++)
						{
							// check if still in y axis bounding
							if (y >= 0 && y < width)
							{
								inflatedImage[x * width * 4 + y * 4 + 0] = 0;
								inflatedImage[x * width * 4 + y * 4 + 1] = 0;
								inflatedImage[x * width * 4 + y * 4 + 2] = 0;
							}
						}
					}
				}

			}
		}

	encodeOneStep("inflatedMap.png", inflatedImage, width, height);
}

