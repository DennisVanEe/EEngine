#pragma once

#include <tinyxml2.h>
#include <string>
#include <iostream>

namespace eeGames
{
	class XMLDocument
	{
	protected:
		tinyxml2::XMLDocument m_xmlFile; // the xml file for defining the entities

	public:
		bool loadContainer(const std::string &dir)
		{
			using namespace tinyxml2;

			XMLError error = m_xmlFile.LoadFile(dir.c_str());
			if (error != XML_SUCCESS)
			{
				std::cout << "[ERROR]: problem loading or parsing xml file at: " << dir << "\n";
				return false;
			}
			return true;
		}
	};
}