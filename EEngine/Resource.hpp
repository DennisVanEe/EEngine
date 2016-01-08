#pragma once

#include <memory>
#include <iostream> //used to write to console prompt
#include <string>

#include <SFML\Graphics.hpp>

namespace eeGames
{
	template<class res_type> class Resource
	{
	private:
		res_type resource;

	public:
		Resource(const std::string & dir)
		{
			resource.loadFromFile(dir);
		}

		const res_type & getTexture() const
		{
			return resource;
		}
	};
}
