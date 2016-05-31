/*
 * ConfigurationManager.h
 *
 *  Created on: May 28, 2016
 *      Author: colman
 */

#include <string>
#include <iostream>
using namespace std;
#include "../Models/Position.h"
#include "../Models/Size.h"

namespace Managers{
	class ConfigurationManager {
	public:
		virtual ~ConfigurationManager();
		static ConfigurationManager* GetInstance();
		void LoadFromFile(string filePath);
		string getPngMapPath();
		Position getStartPosition();
		Position getEndPosition();
		float getPixelPerCm();
		float getPngGridResolution();
		Size getRobotSize();
	private:
		ConfigurationManager();
		static ConfigurationManager * m_ConfigurationManagerInstance;
		string m_PngMapPath;
		float m_PpCM;
		float m_PngGridResolution;
		Position m_StartPosition;
		Position m_EndPosition;
		Size m_RobotSize;
	};
}
