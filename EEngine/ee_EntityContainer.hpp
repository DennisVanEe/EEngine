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
		EntityContainer() {}
		EntityContainer(const EntityContainer& ent) = delete;
		EntityContainer& operator=(const EntityContainer& ent) = delete;

		AnimatedEntity *createAnimatedEntity(const std::string &_p_id, const sf::Texture *_p_texture, uint32_t _p_width,
			uint32_t _p_height, uint8_t _p_columns, uint8_t _p_rows)
		{
			std::unique_ptr<Entity> entity(new AnimatedEntity());
			AnimatedEntity *returnEntity = static_cast<AnimatedEntity*>(entity.get());
			if (!returnEntity->assignTexture(_p_texture, _p_width, _p_height, _p_columns, _p_rows))
				return nullptr;
			_m_allCurrentEntities.insert(std::make_pair(_p_id, _str_Entity(std::move(entity), _e_EntityType::ANIMATED)));
			return returnEntity;
		}
		StaticEntity *createStaticEntity(const std::string &_p_id, const sf::Texture *_p_texture)
		{
			std::unique_ptr<Entity> entity(new StaticEntity());
			StaticEntity *returnEntity = static_cast<StaticEntity*>(entity.get());
			if (!returnEntity->assignTexture(_p_texture))
				return nullptr;
			_m_allCurrentEntities.insert(std::make_pair(_p_id, _str_Entity(std::move(entity), _e_EntityType::STATIC)));
			return returnEntity;
		}
		StaticEntity *createStaticEntity(const std::string &_p_id, const sf::Texture *_p_texture, uint16_t _p_x, uint16_t _p_y,
			uint16_t width, uint16_t height)
		{
			std::unique_ptr<Entity> entity(new StaticEntity());
			StaticEntity *returnEntity = static_cast<StaticEntity*>(entity.get());
			if (!returnEntity->assignTexture(_p_texture, _p_x, _p_y, width, height))
				return nullptr;
			_m_allCurrentEntities.insert(std::make_pair(_p_id, _str_Entity(std::move(entity), _e_EntityType::STATIC)));
			return returnEntity;
		}

		AnimatedEntity *getAnimatedEntity(const std::string &_p_id) const
		{
			auto entityIterator = _m_allCurrentEntities.find(_p_id);
			if (entityIterator == _m_allCurrentEntities.end())
				return nullptr;
			if (entityIterator->second._m_type == _e_EntityType::STATIC)
				return static_cast<AnimatedEntity *>(entityIterator->second._m_entity.get());
			return nullptr;
		}
		StaticEntity *getStaticEntity(const std::string &_p_id) const
		{
			auto entityIterator = _m_allCurrentEntities.find(_p_id);
			if (entityIterator == _m_allCurrentEntities.end())
				return nullptr;
			if (entityIterator->second._m_type == _e_EntityType::STATIC)
				return static_cast<StaticEntity *>(entityIterator->second._m_entity.get());
			return nullptr;
		}

		AnimatedEntity *createAnimatedEntityCopy(const std::string &_p_id, const std::string &_p_idNew)
		{
			AnimatedEntity *returnEntity = getAnimatedEntity(_p_id);
			if (!returnEntity)
				return nullptr;
			std::unique_ptr<Entity> entity(new AnimatedEntity(*returnEntity));
			_m_allCurrentEntities.insert(std::make_pair(_p_idNew, _str_Entity(std::move(entity), _e_EntityType::ANIMATED)));
			return returnEntity;
		}
		StaticEntity *createStaticEntityCopy(const std::string &_p_id, const std::string &_p_idNew)
		{
			StaticEntity *returnEntity = getStaticEntity(_p_id);
			if (!returnEntity)
				return nullptr;
			std::unique_ptr<Entity> entity(new StaticEntity(*getStaticEntity(_p_id)));
			_m_allCurrentEntities.insert(std::make_pair(_p_idNew, _str_Entity(std::move(entity), _e_EntityType::ANIMATED)));
			return returnEntity;
		}

		bool removeEntity(const std::string &id)
		{
			auto entityIterator = _m_allCurrentEntities.find(id);
			if (entityIterator == _m_allCurrentEntities.end())
				return false;
			entityIterator->second._m_entity.release();
			_m_allCurrentEntities.erase(entityIterator);
			return false;
		}
	};
}
