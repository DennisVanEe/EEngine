#pragma once

#include "ee_RequestQueue.hpp"

int eeGames::RequestQueue::findDependency(const std::string &dep) const
{
	for (auto request : _m_requestQueue)
	{
		if (request.second.first->getID() == dep)
			return request.first;
	}
	return -1;
}

bool eeGames::RequestQueue::addRequest(const std::string &target, Request *request)
{
	if (request == nullptr)
	{
		std::cout << "[ERROR]: added request points to NULL";
		return false;
	}
	if (request->getRequest() == RequestType::ERROR_MISMATCH_TYPE)
	{
		std::cout << "[ERROR]: request: " << request->getID() << " has mismatch error\n";
		return false;
	}
		
	int _tmp_priority = request->getPriority();

	// request->AddRef();

	if (_tmp_priority < 0)
	{
		int dep_priority = findDependency(request->getDependency());
		if (dep_priority < 0)
			_m_dependencyCache.push_back(std::make_pair(request, target));
		else
			_m_requestQueue.insert(std::make_pair(dep_priority + 1, std::make_pair(request, target)));
	}
	else
	{
		_m_requestQueue.insert(std::make_pair(_tmp_priority, std::make_pair(request, target)));
	}

	return true;
}

std::multimap<uint16_t, std::pair<eeGames::Request *, std::string>> *eeGames::RequestQueue::getQueue()
{
	return &_m_requestQueue;
}

bool eeGames::RequestQueue::finalizeRequests()
{
	bool success = true;
	int priority;

	for (auto request : _m_dependencyCache)
	{
		priority = findDependency(request.first->getDependency());
		if (priority < 0)
		{
			success = false;
			std::cout << "[ERROR]: Request: " << request.first->getID() << " had finalize request error\n";
		}
		else
			_m_requestQueue.insert(std::make_pair(priority + 1, request));
	}
	
	_m_dependencyCache.clear();
	return success;
}

void eeGames::RequestQueue::clearQueue()
{
	_m_requestQueue.clear();
}