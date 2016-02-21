#pragma once

#include <iostream> // for testing
#include <string>

#include "ee_Request.hpp"
#include "ee_RequestType.hpp"
#include "ee_DataContainerEngine.hpp"
#include "ee_OrderedKeyedData.hpp"
namespace eeGames
{
	class RequestQueue
	{
	private:
		KeyedData<uint16_t, std::pair<Request *, std::string>> _m_requestQueue;
		std::vector<std::pair<Request *, std::string>> _m_dependencyCache; // if dependency is not added yet, it will go here

		int findDependency(const std::string &dep) const; // currently uses slow O(N)
	public:
		bool addRequest(const std::string &target, Request *req);

		std::multimap<uint16_t, std::pair<Request *, std::string>> *getQueue();
		bool finalizeRequests(); // flushes dep_cahce to request queue
		void clearQueue();
	};
}