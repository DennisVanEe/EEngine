#pragma once

#include <unordered_map>
#include <memory>
#include <string>

#include "ee_AnimatedEntity.hpp"
#include "ee_StaticEntity.hpp"

namespace eeGames
{
	enum class _e_EntityType { ANIMATED, STATIC };

	class EntityContainer
	{
	private:
		struct _str_Entity
		{
			std::unique_ptr<Entity> _m_entity;
			_e_EntityType _m_type;
			_str_Entity(std::unique_ptr<Entity> _p_entity, _e_EntityType _p_type) : _m_entity(std::move(_p_entity)), _m_type(_p_type) {}
		};
	private:
		std::unordered_map<std::string, _str_Entity> _m_allCurrentEntities;
	public:
		EntityContainer(const EntityContainer& ent) = delete;
		EntityContainer& operator=(const EntityContainer& ent) = delete;

		AnimatedEntity *createAnimatedEntity(const std::string &_p_id, const sf::Texture *_p_texture, uint32_t _p_width, 
			uint32_t _p_height, uint8_t _p_columns, uint8_t _p_rows)
		{
			std::unique_ptr<Entity> _tmp_entity(new AnimatedEntity());
			AnimatedEntity *_tmp_returnEntity = static_cast<AnimatedEntity*>(_tmp_entity.get());
			_tmp_returnEntity->assign_texture(_p_texture, _p_width, _p_height, _p_columns, _p_rows);
			_m_allCurrentEntities.insert(std::make_pair(_p_id, _str_Entity(std::move(_tmp_entity), _e_EntityType::ANIMATED)));
			return _tmp_returnEntity;
		}	
		StaticEntity *createStaticEntity(const std::string &_p_id, const sf::Texture *_p_texture)
		{
			std::unique_ptr<Entity> _tmp_entity(new StaticEntity());
			StaticEntity *_tmp_returnEntity = static_cast<StaticEntity*>(_tmp_entity.get());
			_tmp_returnEntity->assign_texture(_p_texture);
			_m_allCurrentEntities.insert(std::make_pair(_p_id, _str_Entity(std::move(_tmp_entity), _e_EntityType::STATIC)));
			return _tmp_returnEntity;
		}
		StaticEntity *createStaticEntity(const std::string &_p_id, const sf::Texture *_p_texture, uint16_t _p_x, uint16_t _p_y,
			uint16_t width, uint16_t height)
		{
			std::unique_ptr<Entity> _tmp_entity(new StaticEntity());
			StaticEntity *_tmp_returnEntity = static_cast<StaticEntity*>(_tmp_entity.get());
			_tmp_returnEntity->assign_texture(_p_texture, _p_x, _p_y, width, height);
			_m_allCurrentEntities.insert(std::make_pair(_p_id, _str_Entity(std::move(_tmp_entity), _e_EntityType::STATIC)));
			return _tmp_returnEntity;
		}

		AnimatedEntity *getAnimatedEntity(const std::string &_p_id) const
		{
			auto _tmp_entityIterator = _m_allCurrentEntities.find(_p_id);
			if (_tmp_entityIterator == _m_allCurrentEntities.end())
				return nullptr;
			if (_tmp_entityIterator->second._m_type == _e_EntityType::STATIC)
				return static_cast<AnimatedEntity *>(_tmp_entityIterator->second._m_entity.get());
			return nullptr;
		}
		StaticEntity *getStaticEntity(const std::string &_p_id) const
		{
			auto _tmp_entityIterator = _m_allCurrentEntities.find(_p_id);
			if (_tmp_entityIterator == _m_allCurrentEntities.end())
				return nullptr;
			if (_tmp_entityIterator->second._m_type == _e_EntityType::STATIC)
				return static_cast<StaticEntity *>(_tmp_entityIterator->second._m_entity.get());
			return nullptr;
		}

		bool removeEntity(const std::string &id)
		{
			auto _tmp_EntityIterator = _m_allCurrentEntities.find(id);
			if (_tmp_EntityIterator == _m_allCurrentEntities.end())
				return false;
			_tmp_EntityIterator->second._m_entity.release();
			_m_allCurrentEntities.erase(_tmp_EntityIterator);
			return false;
		}
	};
}
