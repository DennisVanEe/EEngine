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

		CType _container;
	public:
		typename CType::iterator begin()
		{
			return _container.begin();
		}
		typename CType::const_iterator begin() const
		{
			return _container.begin();
		}

		typename CType::iterator end()
		{
			return _container.end();
		}
		typename CType::const_iterator end() const
		{
			return _container.end();
		}

		void clear()
		{
			_container.clear();
		}
		size_t count(const Key &key) const
		{
			return _container.count(key);
		}
		bool empty() const
		{
			return _container.empty();
		}

		size_t erase(const Key &key)
		{
			return _container.erase(key);
		}
		typename CType::iterator erase(typename CType::iterator &it)
		{
			_container.erase(it);
		}

		typename CType::iterator find(const Key &key)
		{
			return _container.find(key);
		}
		typename CType::const_iterator find(const Key &key) const
		{
			return _container.find(key);
		}

		typename CType::iterator insert(std::pair<Key, Data> &element)
		{
			return _container.insert(element);
		}

		size_t size() const
		{
			return _container.size();
		}
		size_t max_size() const
		{
			return _container.max_size();
		}
	};
}

