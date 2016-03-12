#pragma once

#include <map>
#include <memory>
#include <vector>
#include <new>
#include <string>
#include <SFML/Graphics.hpp>

#include "ee_EntityContainerEngine.hpp"
#include "ee_EntityContainerEngine.hpp"
#include "ee_KeyedData.hpp"
#include "ee_OrderedKeyedData.hpp"

namespace eeGames
{
	class RenderEngine
	{
	private:
		EntityContainerEngine *m_entityContainer; // used to construct entities
		sf::RenderWindow m_window;

		std::vector<Entity*> renderBuffer;
	public:
		RenderEngine(EntityContainer *_p_entityContainer)
		{
		}
		RenderEngine(const std::string &_p_name, uint16_t _p_width, uint16_t _p_height, bool _p_fullscreen) 
			: m_window(sf::VideoMode(_p_width, _p_height), _p_name, _p_fullscreen ? sf::Style::Fullscreen : sf::Style::Close)
		{
		}
		
		void setWindowSettings(const std::string &_p_name, uint16_t _p_width, uint16_t _p_height, bool _p_fullscreen)
		{
			m_window.create(sf::VideoMode(_p_width, _p_height), _p_name, _p_fullscreen ? sf::Style::Fullscreen : sf::Style::Close);
		}
		void render();

		void animatedEntityConst(const std::wstring &contID, const std::wstring &entID, void *memory)
		{
			new(memory) AnimatedEntity();
			if (m_entityContainer->getEntityFormCont(contID, entID, memory) == false) // this here should never happen
			{
				throw std::domain_error("entity " + std::string(entID.begin(), entID.end()) + " could not be found in " 
					+ std::string(contID.begin(), entID.end()));
			}
			renderBuffer.push_back(static_cast<AnimatedEntity*>(memory));
			static_cast<AnimatedEntity*>(memory)->assignRenderPos(renderBuffer.end() - 1); // assign the location
		}
		void animatedEntityDest(void *memory)
		{
			renderBuffer.erase(static_cast<AnimatedEntity*>(memory)->getRenderPos());
			static_cast<AnimatedEntity*>(memory)->~AnimatedEntity();
		}

		void staticEntityConst(const std::wstring &contID, const std::wstring &entID, void *memory)
		{
			new(memory) StaticEntity();
			if (m_entityContainer->getEntityFormCont(contID, entID, memory) == false) // this here should never happen
			{
				throw std::domain_error("entity " + std::string(entID.begin(), entID.end()) + " could not be found in "
					+ std::string(contID.begin(), entID.end()));
			}
			renderBuffer.push_back(static_cast<StaticEntity*>(memory));
			static_cast<StaticEntity*>(memory)->assignRenderPos(renderBuffer.end() - 1); // assign the location
		}
		void staticEntityDest(void *memory)
		{
			renderBuffer.erase(static_cast<StaticEntity*>(memory)->getRenderPos());
			static_cast<StaticEntity*>(memory)->~StaticEntity();
		}
	};
}