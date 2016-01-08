#pragma once

#include <string>
#include <assert.h>
#include <unordered_map>

namespace eeGames
{
	template <class object_type> class eeContainer
	{
	private:
		std::unordered_map<std::string, object_type> map;
		std::vector<std::string> names; // used for looping
	public:
		eeContainer();

		void addObject(std::string name, const object_type& obj);
		void removeObject(std::string name);

		object_type& getObject(std::string name);
		const object_type& getConstObject(std::string name) const;
		const std::vector<std::string>& getNameList() const;

		void AddRef() { /*used for Angelscript (does nothing) */ }
		void ReleaseRef() {/*used for Angelscript (does nothing) */ }
	};
}

// due to template classes and linkage issues, definitions are written here

template<class object_type>	eeGames::eeContainer<object_type>::eeContainer()
{
	// does nothing for now
}
template<class object_type> void eeGames::eeContainer<object_type>::addObject(std::string name, const object_type& obj)
{
	std::pair<std::string, object_type> tmpPair(name, obj);
	map.insert(tmpPair);

	// for faster reading:
	names.push_back(name);
}
template<class object_type> void eeGames::eeContainer<object_type>::removeObject(std::string name)
{
	map.erase(name);
	na
}
template<class object_type> object_type& eeGames::eeContainer<object_type>::getObject(std::string name)
{
	std::unordered_map<std::string, object_type>::iterator obj = map.find(name);
	std::cout << name << std::endl;
	assert(obj != map.end());
	return obj->second;
}
template<class object_type> const object_type & eeGames::eeContainer<object_type>::getConstObject(std::string name) const
{
	std::unordered_map<std::string, object_type>::const_iterator obj = map.find(name);
	assert(obj != map.end());
	return obj->second;
}
template<class object_type> const std::vector<std::string>& eeGames::eeContainer<object_type>::getNameList() const
{
	return names;
}

