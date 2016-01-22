#pragma once

#include <map>
#include <memory>
#include <SFML/Graphics.hpp>

#include "ee_Entity.hpp"
#include "ee_StaticEntity.hpp"

namespace eeGames
{
	class RenderEngine
	{
	private:
		std::multimap<uint16_t, const Entity*> _m_entities; //current entities being rendered
		sf::RenderWindow _m_window;

	public:
		RenderEngine()
		{
		}
		RenderEngine(const std::string &_p_name, uint16_t _p_width, uint16_t _p_height, bool _p_fullscreen) 
			: _m_window(sf::VideoMode(_p_width, _p_height), _p_name, _p_fullscreen ? sf::Style::Fullscreen : sf::Style::Close)
		{
		}
		
		void setWindowSettings(const std::string &_p_name, uint16_t _p_width, uint16_t _p_height, bool _p_fullscreen)
		{
			_m_window.create(sf::VideoMode(_p_width, _p_height), _p_name, _p_fullscreen ? sf::Style::Fullscreen : sf::Style::Close);
		}

		void add_entity(uint16_t _p_priority, const Entity *_p_entity)
		{
			_m_entities.insert(std::make_pair(_p_priority, _p_entity));
		}

		void render()
		{
			_m_window.clear();
			for (auto _tmp_entityIterator : _m_entities)
			{
				_m_window.draw(*_tmp_entityIterator.second);
			}
			_m_window.display();
		}
		void clearAllEntities()
		{
			_m_entities.clear();
		}
	};
}