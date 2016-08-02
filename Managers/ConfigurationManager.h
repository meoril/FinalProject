/*
 * Config.h
 *
 *  Created on: May 28, 2016
 *      Author: colman
 */

#ifndef CONFIGURATIONMANAGER_H_
#define CONFIGURATIONMANAGER_H_
#include <string>
#include <vector>
#include "../Models/Position.h"
#include "../Models/Size.h"
using namespace std;

/*
   ConfigurationManager
   Parses and represents a config file
 */
namespace Managers{
class ConfigurationManager {
	public:
		/* Parse the given file
		 */
		ConfigurationManager(string fileName);

		~ConfigurationManager();

		void parse(string fileName);

		string getMapPath();
		Position getStartPosition();
		Position getStartPositionInGrid();
		Point getGoal();
		Point getGoalInGrid();
		Size getRobotSize();
		double getGridMapResolution();
		double getMapResolution();
		double getGridResolution();
		string mapLocation;
		Position startPosition;
		Position* startPositionInGrid;
		Point goal;
		Point* goalInGrid;
		Size robotSize;
		double mapResolutionCm;
		double gridResolutionCm;
	private:
};
}
#endif
