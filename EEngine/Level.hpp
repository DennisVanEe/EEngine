#pragma once

#include <string>
#include <vector>
#include <memory>
#include <fstream>

// SFML API:
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Entity.hpp"
#include "ScriptedEntity.hpp"
//#include "Lighting.hpp"
#include "eeContainer.hpp"
#include "AngelScriptEngine.hpp"

// default names to be aded through xml file later:	

namespace eeGames
{
	class Level
	{
	private:
		eeContainer<Entity> entityContainer;
		eeContainer<ScriptedEntity> scriptedEntityContainer;

		// entities that will be rendered (in specific order)
		std::vector<Entity*> renderEntitities;

		// each level has one view (might add multiple view support in future)
		sf::View view;

		// script engine for each level:
		AngelScriptEngine scriptEngine;

		std::string module;
		std::string stepScript;
	public:
		Level(const eeContainer<Entity> & entities, const eeContainer<ScriptedEntity> & scripted, const std::string & mod, const std::string & stepFuncDir);

		void setUpForRendering();
		
		eeContainer<Entity> & getEntities()
		{
			return entityContainer;
		}
		const eeContainer<Entity> & getEntities() const
		{
			return entityContainer;
		}
		const sf::View & getView() const
		{
			return view;
		}
		const std::vector<Entity*> getRenderEntities() const
		{
			return renderEntitities;
		}

		eeContainer<ScriptedEntity> & getScriptedEntities()
		{
			return scriptedEntityContainer;
		}
		const eeContainer<ScriptedEntity> & getConstScriptedEntities() const
		{
			return scriptedEntityContainer;
		}
		const std::string & getModuleName() const
		{
			return module;
		}
		const std::string & getStepScript() const
		{
			return stepScript;
		}

		inline void step(float frame_time)
		{
			scriptEngine.executeScript(frame_time);
		}

		void AddRef() { /*used for Angelscript (does nothing) */ }
		void ReleaseRef() {/*used for Angelscript (does nothing) */ }
	};
}
