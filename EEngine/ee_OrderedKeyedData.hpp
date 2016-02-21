#pragma once

#pragma once

// This is used so that I can quickly change the data container algorithm to see 
// performance differences

#include <map>

namespace eeGames
{
	template<typename Key, typename Data>
	class OrderedKeyedData
	{
	private:
		typedef std::multimap<Key, Data> CType; // the container design that is being used
	public:
		// all of these methods are based on what you can do with a map
		Data at(const Key &key);
		Data operator[](const Key &key);

		CType::iterator begin();
		CType::const_iterator begin() const;

		CType::iterator end();
		CType::const_iterator end() const;

		void clear();
		size_t count(const Key &key) const;
		bool empty() const;

		size_t erase(const Key &key);
		bool erase(CType::iterator &it);

		CType::iterator find(const Key &key);
		CType::const_iterator find(const Key &key) const;

		CType::iterator &insert(std::pair<Key, Data> &element);

		size_t size() const;
		size_t max_size() const;
	};
}

