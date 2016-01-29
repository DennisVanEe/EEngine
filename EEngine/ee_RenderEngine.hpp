#pragma once

#include <map>
#include <unordered_map>
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

#include "ee_Entity.hpp"
#include "ee_StaticEntity.hpp"

namespace eeGames
{
	class RenderEngine
	{
	private:
		std::multimap<uint16_t, Entity*> _m_entities; //current entities being rendered
		std::unordered_map<std::string, std::multimap<uint16_t, Entity*>::iterator> _m_entityNames;
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

		void addEntity(uint16_t _p_priority, Entity *_p_entity, const std::string &_p_id)
		{
			_m_entityNames.insert(std::make_pair(_p_id, _m_entities.insert(std::make_pair(_p_priority, _p_entity))));
		}
		bool removeEntity(const std::string &_p_id)
		{
			auto nameIterator = _m_entityNames.find(_p_id);
			if (nameIterator == _m_entityNames.end())
				return false;
			_m_entities.erase(nameIterator->second);
			_m_entityNames.erase(nameIterator);
			return true;
		}

		void render()
		{
			_m_window.clear();
			for (auto entityIterator : _m_entities)
			{
				// this is for properly scaling the sprites
				entityIterator.second->setPosition(entityIterator.second->getPosition().x,
					entityIterator.second->getPosition().y * -1);
				_m_window.draw(*entityIterator.second);
				entityIterator.second->setPosition(entityIterator.second->getPosition().x,
					entityIterator.second->getPosition().y * -1);
			}
			_m_window.display();
		}
		void clearAllEntities()
		{
			_m_entities.clear();
			_m_entityNames.clear();
		}
	};
}