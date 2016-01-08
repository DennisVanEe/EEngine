#pragma once

#include <string>
#include <fstream>

#include "Entity.hpp"

namespace eeGames
{
	class ScriptedEntity : public Entity
	{
	private:
		std::string scriptFile;
	public:
		ScriptedEntity(const Resource<sf::Texture> & t, const sf::Vector2f & pos, const sf::Vector2f & org, int zPos, _COL_TYPE type, bool light, bool stat, 
			const std::string& scptDir);

		void loadScript(const std::string& dir); // can be used to change script

		const std::string &getScript() const
		{
			return scriptFile;
		}
	
		void AddRef() { /*used for Angelscript (does nothing) */}
		void ReleaseRef() {/*used for Angelscript (does nothing) */}

		// methods to accessible to AngelScript (only ones that need it):
		// did not use vectors to widen compatibility
		void setPosition(float x, float y)
		{
			Entity::setPosition(sf::Vector2f(x, y));
		}
		void move(float x, float y)
		{
			Entity::move(sf::Vector2f(x, y));
		}
		float getPreviousPositionX() const
		{
			return Entity::getPreviousPosition().x;
		}
		float getPreviousPositionY() const
		{
			return Entity::getPreviousPosition().y;
		}
		float getPositionX() const
		{
			return Entity::getPosition().x;
		}
		float getPositionY() const
		{
			return Entity::getPosition().y;
		}
	};
}
