/*
 * Config.cpp
 *
 *  Created on: May 28, 2016
 *      Author: colman
 */

#include "ConfigurationManager.h"

#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

struct Decleration {
	string name;
	string value;
};

//#include <tr1/regex>
#include <regex.h>
namespace Managers{
	vector<Decleration> readLines(string fileName) {
		vector<Decleration> lines;
		ifstream fileStream(fileName.c_str());
		if (!fileStream) {
			cout << "WAT";
			return lines;
		}
		string line;
		while (getline(fileStream, line)) {
			Decleration lineDec;
			int colon = line.find(':');
			lineDec.name = line.substr(0, colon);
			lineDec.value = line.substr(colon + 2, line.length() - colon - 3);
			lines.push_back(lineDec);
		}
		return lines;
	}

	void parseGoal(ConfigurationManager* config, string value) {
		int space = value.find(' ');
		unsigned x = atoi(value.substr(0, space).c_str());
		unsigned y = atoi(value.substr(space+1).c_str());
		config->goal.m_X = x;
		config->goal.m_Y = y;
	}

	void parseStartLocation(ConfigurationManager* config, string value) {
		int firstSpace = value.find(' ');
		int secondSpace = value.substr(firstSpace+1).find(' ') + firstSpace + 1;
		unsigned x = atoi(value.substr(0, firstSpace).c_str());
		unsigned y = atoi(value.substr(firstSpace+1, secondSpace).c_str());
		unsigned yaw = atoi(value.substr(secondSpace+1).c_str());
		config->startPosition.setX(x);
		config->startPosition.setY(y);
		config->startPosition.m_Yaw = yaw;
	}

	void parseRobotSize(ConfigurationManager* config, string value) {
		int space = value.find(' ');
		unsigned width = atoi(value.substr(0, space).c_str());
		unsigned height = atoi(value.substr(space+1).c_str());
		config->robotSize.m_Width = width;
		config->robotSize.m_Height= height;
	}

	void ConfigurationManager::parse(string fileName) {
		vector<Decleration> decs = readLines(fileName);

		// OMFG its ugly
		for (std::vector<Decleration>::size_type i = 0; i < decs.size(); i++) {
			if (!decs[i].name.compare("goal")) {
				parseGoal(this, decs[i].value);
			} else if (!decs[i].name.compare("map")) {
				this->mapLocation = decs[i].value;
			} else if (!decs[i].name.compare("startLocation")) {
				parseStartLocation(this, decs[i].value);
			} else if (!decs[i].name.compare("robotSize")) {
				parseRobotSize(this, decs[i].value);
			} else if (!decs[i].name.compare("MapResolutionCM")) {
				this->mapResolutionCm = atof(decs[i].value.c_str());
			} else if (!decs[i].name.compare("GridResolutionCM")) {
				this->gridResolutionCm = atof(decs[i].value.c_str());
			}
		}
	}

	ConfigurationManager::ConfigurationManager(string fileName)
		:startPosition(),goal(),robotSize()
	{
		this->mapLocation = string("");
		this->mapResolutionCm = 1.0;
		this->gridResolutionCm = 1.0;
		this->parse(fileName);
	}

	Point ConfigurationManager::getGoal(){
		return goal;
	}

	double ConfigurationManager::getPngGridResolution(){
		return gridResolutionCm;
	}

	double ConfigurationManager::getPixelPerCm(){
		return mapResolutionCm;
	}

	string ConfigurationManager::getMapPath(){
		return mapLocation;
	}

	Size ConfigurationManager::getRobotSize(){
		return robotSize;
	}

	ConfigurationManager::~ConfigurationManager() {

	}
}
