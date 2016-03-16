#pragma once

#include <map>
#include <memory>
#include <vector>
#include <new>
#include <string>
#include <SFML/Graphics.hpp>

#include "ee_EntityContainerEngine.hpp"
#include "ee_EntityContainerEngine.hpp"

namespace eeGames
{
	class RenderEngine
	{
	private:
		EntityContainerEngine *m_entityContainerEngine; // used to construct entities
		sf::RenderWindow m_window;
		sf::Event m_event;

		std::vector<Entity*> renderBuffer;
		bool m_added, m_removed, m_open;

	public:
		RenderEngine(EntityContainerEngine *entityContainerEngine) : 
			m_entityContainerEngine(entityContainerEngine),
			m_added(false),
			m_removed(false),
			m_open(true)
		{
		}

		bool isOpen() { return m_open; }
		
		void setWindowSettings(const std::string &_p_name, uint16_t _p_width, uint16_t _p_height, bool _p_fullscreen)
		{
			m_window.create(sf::VideoMode(_p_width, _p_height), _p_name, _p_fullscreen ? sf::Style::Fullscreen : sf::Style::Close);
			m_window.setVerticalSyncEnabled(true);
		}
		void render();

		void animatedEntityConst(const std::string &contID, const std::string &entID, void *memory)
		{
			new(memory) AnimatedEntity();
			m_entityContainerEngine->getEntityFormCont(contID, entID, memory);

			renderBuffer.push_back(static_cast<AnimatedEntity*>(memory));
			m_added = true;
		}
		void animatedEntityDest(void *memory)
		{
			static_cast<AnimatedEntity*>(memory)->~AnimatedEntity();
			memory = nullptr;
			m_removed = true;
		}

		void staticEntityConst(const std::string &contID, const std::string &entID, void *memory)
		{
			new(memory) StaticEntity();
			m_entityContainerEngine->getEntityFormCont(contID, entID, memory);

			renderBuffer.push_back(static_cast<StaticEntity*>(memory));
			m_added = true;
		}
		void staticEntityDest(void *memory)
		{
			static_cast<AnimatedEntity*>(memory)->~AnimatedEntity();
			memory = nullptr;
			m_removed = true;
		}
		sf::RenderWindow *getWindow()
		{
			return &m_window;
		}
	};
}