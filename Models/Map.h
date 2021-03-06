/*
 * Map.h
 *
 *  Created on: May 28, 2016
 *      Author: colman
 */
#ifndef MAP_H_
#define MAP_H_
#include <vector>
#include <math.h>
#include "../Managers/ConfigurationManager.h"
#include "../Utils/pngUtil.h"
#include "../Utils/lodepng.h"

using namespace Managers;
class Map {
public:
	Map(ConfigurationManager* config);
	Map(unsigned Rows,unsigned Cols);
	~Map();
	unsigned m_Rows;
	unsigned m_Cols;
	std::vector< std::vector<unsigned char> > FatGrid;
	std::vector< std::vector<unsigned char> > RegGrid;

	unsigned width, height;
	void PrintMap(const char* filename);
	bool isPointOccupiedInGrid(Point* pPoint);
	bool isPointOccupiedInMap(Point* pPoint);

	inline unsigned getCols() {
		return m_Cols;
	};

	inline unsigned getRows() {
		return m_Rows;
	};
	std::vector<unsigned char> RegImage;
	std::vector<unsigned char> FatImage;
protected:

private:
	unsigned GridCellSizeInPx;
	void initMap(ConfigurationManager* config);
	int checkCellOccupation(vector<unsigned char> PngMap, int nRow, int nCol);
	std::vector< std::vector<unsigned char> > CreatGridFromMap(std::vector<unsigned char> PngMap,unsigned MapHeight,unsigned MapWidth, float GridResolutionCm, float MapResolution, unsigned &GridCols, unsigned &GridRows);
};
#endif
