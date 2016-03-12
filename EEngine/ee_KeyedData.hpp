#pragma once

// ee_KeyedData 
// Data container that does not garuntee an order

#include <unordered_map>

namespace eeGames
{
	template<typename Key, typename Data> 
	class KeyedData
	{
	private:
		typedef std::unordered_map<Key, Data> CType; // the container design that is being used

		CType _container;
	public:
		Data at(const Key &key)
		{
			return _container.at(key);
		}
		Data operator[](const Key &key)
		{
			return _container.at(key);
		}

		CType::iterator begin()
		{
			return _container.begin();
		}
		CType::const_iterator begin() const
		{
			return _container.begin();
		}

		CType::iterator end()
		{
			return _container.end();
		}
		CType::const_iterator end() const
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
		CType::iterator erase(CType::iterator &it)
		{
			return _container.erase(it);
		}

		CType::iterator find(const Key &key)
		{
			return _container.find(key);
		}
		CType::const_iterator find(const Key &key) const
		{
			return _container.find(key);
		}

		std::pair<CType::iterator, bool> &insert(std::pair<Key, Data> &element)
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
