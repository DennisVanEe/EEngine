#pragma once

#include <vector>

#include "ee_Request.hpp"

namespace eeGames
{
	class RequestManager
	{
	private:
		std::vector<Request*> requests;
	public:
		Request *create(const std::string &i, int p, RequestType rt);
		Request *create(const std::string &i, const std::string &dep, RequestType rt);
		void delete_all();
	};
}