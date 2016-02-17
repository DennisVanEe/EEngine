#include "ee_Request.hpp"

// the create_request form:

eeGames::Request *eeGames::create_request(const std::string &i, uint16_t p, RequestType rt)
{
	return new Request(i, p, rt);
}

eeGames::Request *eeGames::create_request(const std::string &i, const std::string &dep, RequestType rt)
{
	return new Request(i, dep, rt);
}



