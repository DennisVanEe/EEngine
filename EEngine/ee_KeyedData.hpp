#pragma once

// This is used so that I can quickly change the data container algorithm to see 
// performance differences

#include <map>

namespace eeGames
{
	template<typename Key, typename Data> 
	class KeyedData
	{
	private:
		std::map<Key, Data> _container;
	public:
		// all of these methods are based on what you can do with a map
		Data at(Key key);
		Data operator[](Key key);

		std::map<Key, Data>::iterator begin();
		std::map<Key, Data>::const_iterator begin() const;

		void clear();

	};
}
