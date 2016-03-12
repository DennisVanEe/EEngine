#pragma once

namespace eeGames
{
	enum class RequestType
	{
		// data dependent 
		WRITE_DATA, 
		READ_DATA,

		// non data dependent
		TERMINATE_MODULE,
		CREATE_MODULE,
		SLEEP_MODULE,
		WAKE_MODULE,
		CREATE_CONTAINER,
		REMOVE_CONTAINER,
		WRITE_CONTAINER_FILE,
		READ_CONTAINER_FILE,

		// a non data request can't use a data dependent request type
		ERROR_MISMATCH_TYPE
	};
}
