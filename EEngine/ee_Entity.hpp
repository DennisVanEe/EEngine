#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

namespace eeGames
{
	enum class EntityType { ANIMATED, STATIC };

	class Entity : public sf::Transformable, public sf::Drawable
	{
	protected:
		EntityType m_type;

		int renderLev;
		bool render;
	public:

		void setRenderLevel(int lev) { lev < 0 ? renderLev = 0 : renderLev = lev; }
		int getRenderLevel() { return renderLev; }

		void setVisible(bool vis) { render = vis; }
		bool isVisible() { return render; }

		EntityType getType() const { return m_type; }

		float getPositionX() const { return getPosition().x; }
		float getPositionY() const { return getPosition().y; }
		float getScaleX() const { return getScale().x; }
		float getScaleY() const { return getScale().y; }
		float getOriginX() const { return getOrigin().x; }
		float getOriginY() const { return getOrigin().y; }

		bool operator>(const Entity& other) { return renderLev > other.renderLev; }
		bool operator<(const Entity& other) { return renderLev < other.renderLev; }
		bool operator>=(const Entity& other) { return renderLev >= other.renderLev; }
		bool operator<=(const Entity& other) { return renderLev <= other.renderLev; }
		bool operator==(const Entity& other) { return renderLev == other.renderLev; }
	};
}
