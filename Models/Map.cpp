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
}

void Map::initMap(const char* filename) {
    unsigned x, y, bX, bY;
    
    // Get the config
    ConfigurationManager* config = new ConfigurationManager(filename);
    
    //decode
    unsigned error = lodepng::decode(RegImage, width, height,
                                     config->getMapPath());
    
    //if there's an error, display it
    if (error)
        std::cout << "decoder error " << error << ": "
        << lodepng_error_text(error) << std::endl;
    
    // Create the fat img
    FatImage.resize(width * height * 4);
    
    // calc the size of the robot in pic px
    unsigned PxToBlow = ceil(
                             config->getRobotSize().RadiosSize()
                             / config->getPngGridResolution());
    
    cout <<RegImage.size();
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
    
    // create grid from the fat and regular map
    this->FatGrid = this->CreatGridFromMap(FatImage, height, width,
                                           config->getPngGridResolution(), config->getPixelPerCm(),
                                           this->m_Cols, this->m_Rows);
    
    
    
    this->RegGrid = this->CreatGridFromMap(RegImage, height, width,
                                           config->getPngGridResolution(), config->getPixelPerCm(),
                                           this->m_Cols, this->m_Rows);
    
}

std::vector< std::vector<unsigned char> > Map::CreatGridFromMap(std::vector<unsigned char> PngMap,
                                                                unsigned MapHeight, unsigned MapWidth, float GridResolutionCm,
                                                                float PixelPerCm, unsigned& GridCols, unsigned& GridRows) {
    
    // Calc grid size
    unsigned GridCellSizeInPx = ceil(GridResolutionCm / PixelPerCm);
    GridCols = ceil(MapWidth * PixelPerCm / GridResolutionCm);
    GridRows = ceil(MapHeight * PixelPerCm / GridResolutionCm);
    
    RegGrid.resize(GridCols);
    
    for (int i = 0; i < GridCols; i++){
        RegGrid[i].resize(GridRows);
    }
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
                RegGrid[i][j] = 1;
            } else {
                // Black
                RegGrid[i][j] = 0;
            }
            
        }
        
    }
    
    return RegGrid;
    
}
Map::~Map() {
}

