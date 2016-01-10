#pragma once

#include <map>
#include <iostream> // for testing
#include <string>

#include "ee_Request.hpp"
#include "ee_RequestType.hpp"
#include "ee_DataContainerEngine.hpp"

namespace eeGames
{
	class RequestQueue
	{
	private:
		std::multimap<uint16_t, std::pair<Request *, std::string>> request_queue;
		std::vector<std::pair<Request *, std::string>> dep_cache; // if dependency is not added yet, it will go here

		int find_dependency(const std::string &dep) const; // currently uses slow O(N)
	public:
		bool add_request(const std::string &target, Request *req);

		std::multimap<uint16_t, std::pair<Request *, std::string>> *get_queue();
		bool finalize_requests(); // flushes dep_cahce to request queue
		void clear_queue();
	};
}