/*
 * Map.cpp
 *
 *  Created on: May 28, 2016
 *      Author: colman
 */

#include "Map.h"
using namespace std;

Map::Map(const char* filename) {
	initMap(filename);
}

Map::Map(unsigned Cols, unsigned Rows) {
	this->m_Cols = Cols;
	this->m_Rows = Rows;
	this->FatGrid.resize(Rows, Cols);
	this->RegGrid.resize(Rows, Cols);
}

void Map::initMap(const char* filename) {
	std::vector<unsigned char> image;
	std::vector<unsigned char> FatImage;
	unsigned width, height;
	unsigned x, y, bX, bY;

	// Get the config
	ConfigurationManager* config = ConfigurationManager::GetInstance();

	//decode
	unsigned error = lodepng::decode(image, width, height,
			config->getPngMapPath());

	//if there's an error, display it
	if (error)
		std::cout << "decoder error " << error << ": "
				<< lodepng_error_text(error) << std::endl;

	// Create the fat img
	FatImage.resize(width * height);

	// calc the size of the robot in pic px
	unsigned PxToBlow = ceil(
			config->getRobotSize().RadiosSize()
					/ config->getPngGridResolution());

	// run on the map and find the
	unsigned char color;
	for (y = 0; y < height; y++)
		for (x = 0; x < width; x++) {
			if (image[y * width * 4 + x * 4 + 0]
					|| image[y * width * 4 + x * 4 + 1]
					|| image[y * width * 4 + x * 4 + 2])
				color = 0;

			// add oppstical to the fat img
			for (bX = std::max(x - PxToBlow, static_cast<unsigned int>(0));
					bX < PxToBlow + x; bX++)
				for (bY = std::max(x - PxToBlow, static_cast<unsigned int>(0));
						bY < PxToBlow + y; bY++) {
					FatImage[y * width * 4 + x * 4 + 0] = color;
					FatImage[y * width * 4 + x * 4 + 1] = color;
					FatImage[y * width * 4 + x * 4 + 2] = color;
					FatImage[y * width * 4 + x * 4 + 3] = 255;
				}
		}

	// create grid from the fat and regular map

	this->FatGrid = this->CreatGridFromMap(FatImage, height, width,
			config->getPngGridResolution(), config->getPixelPerCm(),
			this->m_Cols, this->m_Rows);


	unsigned error2 = lodepng::encode("try.png", this->FatGrid, width, height);

	this->RegGrid = this->CreatGridFromMap(image, height, width,
			config->getPngGridResolution(), config->getPixelPerCm(),
			this->m_Cols, this->m_Rows);

}

std::vector<unsigned char> Map::CreatGridFromMap(std::vector<unsigned char> PngMap,
		unsigned MapHeight, unsigned MapWidth, float GridResolutionCm,
		float PixelPerCm, unsigned& GridCols, unsigned& GridRows) {

	// Calc grid size
	unsigned GridCellSizeInPx = ceil(GridResolutionCm / PixelPerCm);
	GridCols = ceil(MapWidth * PixelPerCm / GridResolutionCm);
	GridRows = ceil(MapHeight * PixelPerCm / GridResolutionCm);

	//crate the grid
	std::vector<unsigned char> Grid;
	Grid.resize(GridCols, GridRows);

	for (unsigned i = 0; i < GridCols; ++i) {
		for (unsigned j = 0; j < GridRows; ++j) {

			// defind white px counter
			unsigned PxWhiteConuter = 0;

			// find out from the png if cell is black or white
			for (unsigned pI = 0; pI < GridCellSizeInPx; ++pI) {
				for (unsigned pJ = 0; pJ < GridCellSizeInPx; ++pJ) {
					PxWhiteConuter += PngMap[(i * GridCellSizeInPx * MapWidth
							+ pI) * 4 + (j * GridCellSizeInPx + pJ) * 4];
				}
			}

			// Chack for number of black cell TODO:think if i need a parameter for Negligible number of blac px
			if (PxWhiteConuter == (GridCellSizeInPx * GridCellSizeInPx)) {
				// white
				Grid[i * GridCols + j] = 1;
			} else {
				// Black
				Grid[i * GridCols + j] = 0;
			}

		}

	}

	return Grid;

}
Map::~Map() {
}

