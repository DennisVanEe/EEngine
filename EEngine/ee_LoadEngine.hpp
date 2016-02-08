#pragma once

#include "ee_Module.hpp"
#include "ee_RequestQueue.hpp"
#include "ee_DataContainerEngine.hpp"
#include "ee_RequestType.hpp"
#include "ee_EntityContainer.hpp"
#include "ee_ScriptInterface.hpp"
#include "ee_SoundContainer.hpp"
#include "ee_RenderEngine.hpp"
#include "ee_ResourceEngine.hpp"

namespace eeGames
{
	class LoadEngine
	{
	private:
		DataContainerEngine *_m_dataContainerEngine;
		EntityContainer *_m_entityContainer;
		SoundContainer *_m_soundContainer;
		ResourceEngine *_m_resourceEngine;

		asIScriptEngine *_m_engine;
	public:
		LoadEngine(DataContainerEngine *_p_dataContainerEngine, EntityContainer *_p_entityContainer,
			SoundContainer *_p_soundContainer, ResourceEngine *_p_resourceEngine) : _m_dataContainerEngine(_p_dataContainerEngine),
			_m_entityContainer(_p_entityContainer), _m_soundContainer(_p_soundContainer), _m_resourceEngine(_p_resourceEngine)
		{
		}

		// wrappers for adding data
		bool addDataWrapper(const std::string &_p_name, const std::string &_p_dataName, float *_p_data)
		{
			return _m_dataContainerEngine->addData(_p_name, DataType::FLOAT, _p_dataName, reinterpret_cast<byte *>(_p_data));
		}
		bool addDataWrapper(const std::string &_p_name, const std::string &_p_dataName, char *_p_data);
		bool addDataWrapper(const std::string &_p_name, const std::string &_p_dataName, int *_p_data);
		bool addDataWrapper(const std::string &_p_name, const std::string &_p_dataName, const std::string *_p_data);
		bool addDataWrapper(const std::string &_p_name, const std::string &_p_dataName, bool *_p_data);

		bool getDataWrapper(const std::string &_p_dataName, float *_p_data);
		bool getDataWrapper(const std::string &_p_dataName, char *_p_data);
		bool getDataWrapper(const std::string &_p_dataName, int *_p_data);
		bool getDataWrapper(const std::string &_p_dataName, const std::string *_p_data);
		bool getDataWrapper(const std::string &_p_dataName, bool *_p_data);
	};
}
