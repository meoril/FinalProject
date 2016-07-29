/*
 * Map.cpp
 *
 *  Created on: May 28, 2016
 *      Author: colman
 */

#include "Map.h"
using namespace std;

Map::Map(ConfigurationManager* config) {
    initMap(config);
}

void Map::initMap(ConfigurationManager* config) {
    
    //decode
    unsigned error = lodepng::decode(RegImage, width, height,
                                     config->getMapPath());
    
    //if there's an error, display it
    if (error)
    std::cout << "decoder error " << error << ": "
				<< lodepng_error_text(error) << std::endl;
    
    int stam = RegImage.size();
    
    // Create the fat img
    FatImage.resize(width * height * 4);
    
    // calc the size of the robot in pic px
    unsigned PxToBlow = ceil(
                             config->getRobotSize().RadiosSize()
                             / config->getGridResolution());
    
    // Paint the new map image in white
    for(unsigned int i = 0; i < RegImage.size(); i++)
    {
        FatImage[i] = RegImage[i];
    }
    
    
    for (unsigned int i = 0; i < height; i++)
    for (unsigned int j = 0; j < width; j++) {
        if ((RegImage[i * width * 4 + j * 4 + 0] == 0) &&
            (RegImage[i * width * 4 + j * 4 + 1] == 0) &&
            (RegImage[i * width * 4 + j * 4 + 2] == 0))
        {
            
            for(unsigned int x =i-PxToBlow; x<=i+PxToBlow;x++)
            {
                // check if still in x axis bounding
                if (x >= 0 && x < height)
                {
                    for (unsigned int y=j-PxToBlow; y<=j+PxToBlow; y++)
                    {
                        // check if still in y axis bounding
                        if (y >= 0 && y < width)
                        {
                            FatImage[x * width * 4 + y * 4 + 0] = 0;
                            FatImage[x * width * 4 + y * 4 + 1] = 0;
                            FatImage[x * width * 4 + y * 4 + 2] = 0;
                        }
                    }
                }
            }
            
        }
    }
    
    int bla = FatImage.size();
    // create grid from the fat map
    this->FatGrid = this->CreatGridFromMap(FatImage, height, width,
                                           config->getGridResolution(), config->getMapResolution(),
                                           this->m_Cols, this->m_Rows);
    
    // create grid from the regular map
    this->RegGrid = this->CreatGridFromMap(RegImage, height, width,
                                           config->getGridResolution(), config->getMapResolution(),
                                           this->m_Cols, this->m_Rows);
    
}

int Map::checkCellOccupation(std::vector<unsigned char> PngMap, int nRow, int nCol){
    nRow *= GridCellSizeInPx;
    nCol *= GridCellSizeInPx;
    
    for (unsigned int currRow = 0; currRow < GridCellSizeInPx; currRow++){
        for (unsigned int currCol = 0; currCol < GridCellSizeInPx; currCol++){
            if (PngMap[((nRow + currRow) * width * 4) + ((nCol + currCol) * 4)] != 255){
                return 1;
            }
        }
    }
    
    return 0;
}

std::vector< std::vector<unsigned char> > Map::CreatGridFromMap(std::vector<unsigned char> PngMap,
                                                                unsigned MapHeight, unsigned MapWidth, float GridResolutionCm,
                                                                float MapResolution, unsigned& GridCols, unsigned& GridRows) {
    
    // Calc grid size
    GridCellSizeInPx = ceil(GridResolutionCm / MapResolution);
    GridCols = ceil(MapWidth * MapResolution / GridResolutionCm);
    GridRows = ceil(MapHeight * MapResolution / GridResolutionCm);
    
    vector< vector<unsigned char> > tempGrid;
    tempGrid.resize(GridCols);
    
    for (unsigned int i = 0; i < GridCols; i++){
        tempGrid[i].resize(GridRows);
    }
    
    for (unsigned i = 0; i < GridCols; ++i) {
        for (unsigned j = 0; j < GridRows; ++j) {
            tempGrid[i][j] = this->checkCellOccupation(PngMap, i, j);
        }
    }
    
    return tempGrid;
}

bool Map::isPointOccupiedInGrid(Point* pPoint){
    return !this->FatGrid[pPoint->getY()][pPoint->getX()];
}

bool Map::isPointOccupiedInMap(Point* pPoint){
    return !this->FatImage[pPoint->getY() * 4 + pPoint->getX() * width * 4];
}

Map::~Map() {
}

