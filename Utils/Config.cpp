/*
 * Config.cpp
 *
 *  Created on: May 28, 2016
 *      Author: colman
 */

#include "Config.h"

#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

struct Decleration {
	string name;
	string value;
};

#include <tr1/regex>
#include <regex.h>

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

void parseGoal(Config* config, string value) {
	int space = value.find(' ');
	unsigned x = atoi(value.substr(0, space).c_str());
	unsigned y = atoi(value.substr(space+1).c_str());
	config->goal[0] = x;
	config->goal[1] = y;
}

void parseStartLocation(Config* config, string value) {
	int firstSpace = value.find(' ');
	int secondSpace = value.substr(firstSpace+1).find(' ') + firstSpace + 1;
	unsigned x = atoi(value.substr(0, firstSpace).c_str());
	unsigned y = atoi(value.substr(firstSpace+1, secondSpace).c_str());
	unsigned yaw = atoi(value.substr(secondSpace+1).c_str());
	config->startPosition[0] = x;
	config->startPosition[1] = y;
	config->startPosition[2] = yaw;
}

void parseRobotSize(Config* config, string value) {
	int space = value.find(' ');
	unsigned width = atoi(value.substr(0, space).c_str());
	unsigned height = atoi(value.substr(space+1).c_str());
	config->robotSize[0] = width;
	config->robotSize[1] = height;
}

void Config::parse(string fileName) {
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

	// Debug it
	cout << "map location: " << this->mapLocation << endl
		 << "start location: " << this->startPosition[0] << " "
		 	 	 	 	 	  << this->startPosition[1] << " "
		 	 	 	 	 	  << this->startPosition[2] << endl
		 << "goal: " << this->goal[0] << " " << this->goal[1] << endl
		 << "robot size: " << this->robotSize[0] << " " << this->robotSize[1] << endl
		 << "map res: " << this->mapResolutionCm << endl
		 << "grid res: " << this->gridResolutionCm << endl
		 ;
}

Config::Config(string fileName) {
	this->mapLocation = string("");
	this->startPosition = new int[3];
	this->goal = new int[2];
	this->robotSize = new int[2];
	this->mapResolutionCm = 1.0;
	this->gridResolutionCm = 1.0;
	this->parse(fileName);
}

Config::~Config() {
	delete[] this->goal;
	delete[] this->startPosition;
	delete[] this->robotSize;
}
