#include "ee_RequestManager.hpp"
#include <iostream>

eeGames::Request *eeGames::RequestManager::create(const std::string &i, int p, RequestType rt)
{
	std::cout << "stage A\n";
	Request *temp = new Request(i, p, rt);
	std::cout << "stage B\n";
	requests.push_back(temp);
	std::cout << "stage C\n";
	return temp;
}

eeGames::Request *eeGames::RequestManager::create(const std::string &i, const std::string &dep, RequestType rt)
{
	Request *temp = new Request(i, dep, rt);
	requests.push_back(temp);
	return temp;
}

void eeGames::RequestManager::delete_all()
{
	for (Request *temp : requests)
		delete temp;
	requests.clear();
}
