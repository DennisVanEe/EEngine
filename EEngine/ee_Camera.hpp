#pragma once

#include <SFML/Graphics.hpp>
#include <new>

// for now it is simply a wrapper
namespace eeGames
{
	class Camera : public sf::View
	{ 
	public:
		Camera(float xc, float yc, float xw, float xh)
		{
			sf::View(sf::Vector2f(xc, yc), sf::Vector2f(xw, xh));
		}
	};

	void CameraConst(float xc, float yc, float xw, float xh, void *memory)
	{
		new(memory) Camera(xc, yc, xw, xh);
	}

	void CameraDest(void *memory)
	{
		static_cast<Camera*>(memory)->~Camera();
	}
}