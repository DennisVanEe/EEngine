#pragma once

#include "ee_RequestQueue.hpp"

int eeGames::RequestQueue::find_dependency(const std::string &dep) const
{
	for (auto req : request_queue)
	{
		if (req.second.first->get_id() == dep)
			return req.first;
	}
	return -1;
}

bool eeGames::RequestQueue::add_request(const std::string &target, Request *request)
{
	if (request == nullptr)
	{
		std::cout << "[ERROR]: added request points to NULL";
		return false;
	}
	if (request->get_request() == RequestType::ERROR_MISMATCH_TYPE)
	{
		std::cout << "[ERROR]: request: " << request->get_id() << " has mismatch error\n";
		return false;
	}
		
	int temp_priority = request->get_priority();

	// request->AddRef();

	if (temp_priority < 0)
	{
		int dep_priority = find_dependency(request->get_dependency());
		if (dep_priority < 0)
			dep_cache.push_back(std::make_pair(request, target));
		else
			request_queue.insert(std::make_pair(dep_priority + 1, std::make_pair(request, target)));
	}
	else
	{
		request_queue.insert(std::make_pair(temp_priority, std::make_pair(request, target)));
	}

	return true;
}

std::multimap<int, std::pair<eeGames::Request *, std::string>> *eeGames::RequestQueue::get_queue()
{
	return &request_queue;
}

bool eeGames::RequestQueue::finalize_requests()
{
	bool success = true;
	int priority;

	for (auto req : dep_cache)
	{
		priority = find_dependency(req.first->get_dependency());
		if (priority < 0)
			success = false;
		else
			request_queue.insert(std::make_pair(priority + 1, req));
	}
	
	dep_cache.clear();
	return success;
}

void eeGames::RequestQueue::clear_queue()
{
	request_queue.clear();
}