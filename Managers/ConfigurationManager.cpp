/*
 * ConfigurationManager.cpp
 *
 *  Created on: May 28, 2016
 *      Author: colman
 */
#include <iostream>
#include <string>

#include "../Utils/Config.h"

#include "ConfigurationManager.h"
using namespace std;
namespace Managers{

	ConfigurationManager::ConfigurationManager(){};

	ConfigurationManager *ConfigurationManager::m_ConfigurationManagerInstance = NULL;
	void ConfigurationManager::LoadFromFile(string filePath) {
			// create the first singleton instance

			Config configParser(filePath);

			ConfigurationManager::m_ConfigurationManagerInstance = new ConfigurationManager();
			m_PngMapPath = configParser.mapLocation;
			m_StartPosition.m_X = configParser.startPosition[0];
			m_StartPosition.m_Y = configParser.startPosition[1];
			m_StartPosition.m_Yaw = configParser.startPosition[2];
			m_EndPosition.m_X = configParser.goal[0];
			m_EndPosition.m_Y = configParser.goal[1];
			m_PpCM = configParser.mapResolutionCm;
			m_PngGridResolution = configParser.gridResolutionCm;
			m_RobotSize.m_Width = configParser.robotSize[0];
			m_RobotSize.m_Height = configParser.robotSize[1];

		}

	ConfigurationManager::~ConfigurationManager() {
		}


	ConfigurationManager* ConfigurationManager::GetInstance() {
		if (ConfigurationManager::m_ConfigurationManagerInstance == NULL)
		{
			throw new std::string("Object ConfigurationManager Never Loaded");
		}
		else
		{
			return ConfigurationManager::m_ConfigurationManagerInstance;
		}
		return NULL;
		}


		string ConfigurationManager::getPngMapPath() {
			return m_PngMapPath;
		}

		Position ConfigurationManager::getStartPosition() {
			return m_StartPosition;
		}

		Position ConfigurationManager::getEndPosition() {
			return m_EndPosition;
		}

		float ConfigurationManager::getPixelPerCm() {
			return m_PpCM;
		}

		float ConfigurationManager::getPngGridResolution() {
			return m_PngGridResolution;
		}

		Size ConfigurationManager::getRobotSize() {
			return m_RobotSize;
		}

	}
