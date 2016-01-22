#include "ee_Request.hpp"

void eeGames::Request::addData(void *_p_data, DataType _p_dataType)
{
	_m_dataType = _p_dataType;
	switch (_p_dataType)
	{
	case DataType::INT:
		_m_data = new byte[sizeof(int)];
		memcpy(_m_data, _p_data, sizeof(int));
		break;
	case DataType::FLOAT:
		_m_data = new byte[sizeof(float)];
		memcpy(_m_data, _p_data, sizeof(float));
		break;
	case DataType::DOUBLE:
		_m_data = new byte[sizeof(double)];
		memcpy(_m_data, _p_data, sizeof(double));
		break;
	case DataType::BOOL:
		_m_data = new byte[sizeof(bool)];
		memcpy(_m_data, _p_data, sizeof(bool));
		break;
	case DataType::STRING:
		_m_data = new byte[reinterpret_cast<std::string*>(_p_data)->length() + 1];
		int len = reinterpret_cast<std::string*>(_p_data)->length() + 1;
		memcpy(_m_data, reinterpret_cast<std::string*>(_p_data)->c_str(), reinterpret_cast<std::string*>(_p_data)->length() + 1);
		break;
	}
}

int eeGames::Request::getInt(bool *t)
{
	if (_m_requestType != RequestType::READ_DATA)
	{
		*t = false;
		return 0;
	}

	if (_m_data == nullptr)
	{
		*t = false;
		return 0;
	}

	return *reinterpret_cast<int*>(_m_data);
}

int eeGames::Request::getInt()
{
	if (_m_data == nullptr)
		return 0;
	return *reinterpret_cast<int*>(_m_data);
}

float eeGames::Request::getFloat(bool *t)
{
	if (_m_requestType != RequestType::READ_DATA)
	{
		*t = false;
		return 0.f;
	}

	if (_m_data == nullptr)
	{
		*t = false;
		return 0.f;
	}

	return *reinterpret_cast<float*>(_m_data);
}

float eeGames::Request::getFloat()
{
	if (_m_data == nullptr)
		return 0.f;
	return *reinterpret_cast<float*>(_m_data);
}

double eeGames::Request::getDouble(bool *t)
{
	if (_m_requestType != RequestType::READ_DATA)
	{
		*t = false;
		return 0.0;
	}

	if (_m_data == nullptr)
	{
		*t = false;
		return 0.0;
	}

	return *reinterpret_cast<double*>(_m_data);
}

double eeGames::Request::getDouble()
{
	if (_m_data == nullptr)
		return 0.0;
	return *reinterpret_cast<double*>(_m_data);
}

bool eeGames::Request::getBool(bool *t)
{
	if (_m_requestType != RequestType::READ_DATA)
	{
		*t = false;
		return false;
	}

	if (_m_data == nullptr)
	{
		*t = false;
		return false;
	}

	return *reinterpret_cast<bool*>(_m_data);
}

bool eeGames::Request::getBool()
{
	if (_m_data == nullptr)
		return false;
	return *reinterpret_cast<bool*>(_m_data);
}

std::string eeGames::Request::getString(bool *t)
{
	if (_m_requestType != RequestType::READ_DATA)
	{
		*t = false;
		return "";
	}

	if (_m_data == nullptr)
	{
		*t = false;
		return "";
	}

	return std::string(_m_data);
}

std::string eeGames::Request::getString()
{
	if (_m_data == nullptr)
		return "";
	return std::string(_m_data);
}

// the create_request form:

eeGames::Request *eeGames::create_request(const std::string &i, uint16_t p, RequestType rt)
{
	if (rt == RequestType::CREATE_MODULE && rt == RequestType::READ_CONTAINER_FILE && rt == RequestType::READ_DATA && rt == RequestType::WRITE_CONTAINER_FILE
		&& rt == RequestType::WRITE_DATA)
		rt = RequestType::ERROR_MISMATCH_TYPE;
	return new Request(i, p, rt);
}
eeGames::Request *eeGames::create_request(const std::string &i, uint16_t p, RequestType rt, const std::string &d1)
{
	if (rt == RequestType::WRITE_DATA && rt == RequestType::CREATE_CONTAINER && rt == RequestType::REMOVE_CONTAINER
		&& rt == RequestType::SLEEP_MODULE && rt == RequestType::TERMINATE_MODULE && rt == RequestType::WAKE_MODULE)
		rt = RequestType::ERROR_MISMATCH_TYPE;
	Request *temp = new Request(i, p, rt);
	temp->addTargetName(d1);
	return temp;
}
eeGames::Request *eeGames::create_request(const std::string &i, uint16_t p, RequestType rt, const std::string &d1, int *d2)
{
	if (rt != RequestType::WRITE_DATA)
		rt = RequestType::ERROR_MISMATCH_TYPE;
	Request *temp = new Request(i, p, rt);
	temp->addData(d2, DataType::INT);
	temp->addTargetName(d1);
	return temp;
}
eeGames::Request *eeGames::create_request(const std::string &i, uint16_t p, RequestType rt, const std::string &d1, float *d2)
{
	if (rt != RequestType::WRITE_DATA)
		rt = RequestType::ERROR_MISMATCH_TYPE;
	Request *temp = new Request(i, p, rt);
	temp->addData(d2, DataType::FLOAT);
	temp->addTargetName(d1);
	return temp;
}
eeGames::Request *eeGames::create_request(const std::string &i, uint16_t p, RequestType rt, const std::string &d1, double *d2)
{
	if (rt != RequestType::WRITE_DATA)
		rt = RequestType::ERROR_MISMATCH_TYPE;
	Request *temp = new Request(i, p, rt);
	temp->addData(d2, DataType::DOUBLE);
	temp->addTargetName(d1);
	return temp;
}
eeGames::Request *eeGames::create_request(const std::string &i, uint16_t p, RequestType rt, const std::string &d1, bool *d2)
{
	if (rt != RequestType::WRITE_DATA)
		rt = RequestType::ERROR_MISMATCH_TYPE;
	Request *temp = new Request(i, p, rt);
	temp->addData(d2, DataType::BOOL);
	temp->addTargetName(d1);
	return temp;
}
eeGames::Request *eeGames::create_request(const std::string &i, uint16_t p, RequestType rt, const std::string &d1, std::string &d2)
{
	if (rt != RequestType::WRITE_DATA)
		rt = RequestType::ERROR_MISMATCH_TYPE;
	Request *temp = new Request(i, p, rt);
	temp->addData(&d2, DataType::STRING);
	temp->addTargetName(d1);
	return temp;
}

eeGames::Request *eeGames::create_request(const std::string &i, const std::string &dep, RequestType rt)
{
	if (rt == RequestType::CREATE_MODULE && rt == RequestType::READ_CONTAINER_FILE && rt == RequestType::READ_DATA && rt == RequestType::WRITE_CONTAINER_FILE
		&& rt == RequestType::WRITE_DATA)
		rt = RequestType::ERROR_MISMATCH_TYPE;
	return new Request(i, dep, rt);
}
eeGames::Request *eeGames::create_request(const std::string &i, const std::string &dep, RequestType rt, const std::string &d1)
{
	if (rt == RequestType::WRITE_DATA && rt == RequestType::CREATE_CONTAINER && rt == RequestType::REMOVE_CONTAINER
		&& rt == RequestType::SLEEP_MODULE && rt == RequestType::TERMINATE_MODULE && rt == RequestType::WAKE_MODULE)
		rt == RequestType::ERROR_MISMATCH_TYPE;
	Request *temp = new Request(i, dep, rt);
	temp->addTargetName(d1);
	return temp;
}
eeGames::Request *eeGames::create_request(const std::string &i, const std::string &dep, RequestType rt, const std::string &d1, int *d2)
{
	if (rt != RequestType::WRITE_DATA)
		rt = RequestType::ERROR_MISMATCH_TYPE;
	Request *temp = new Request(i, dep, rt);
	temp->addData(d2, DataType::INT);
	temp->addTargetName(d1);
	return temp;
}
eeGames::Request *eeGames::create_request(const std::string &i, const std::string &dep, RequestType rt, const std::string &d1, float *d2)
{
	if (rt != RequestType::WRITE_DATA)
		rt = RequestType::ERROR_MISMATCH_TYPE;
	Request *temp = new Request(i, dep, rt);
	temp->addData(d2, DataType::FLOAT);
	temp->addTargetName(d1);
	return temp;
}
eeGames::Request *eeGames::create_request(const std::string &i, const std::string &dep, RequestType rt, const std::string &d1, double *d2)
{
	if (rt != RequestType::WRITE_DATA)
		rt = RequestType::ERROR_MISMATCH_TYPE;
	Request *temp = new Request(i, dep, rt);
	temp->addData(d2, DataType::DOUBLE);
	temp->addTargetName(d1);
	return temp;
}
eeGames::Request *eeGames::create_request(const std::string &i, const std::string &dep, RequestType rt, const std::string &d1, bool *d2)
{
	if (rt != RequestType::WRITE_DATA)
		rt = RequestType::ERROR_MISMATCH_TYPE;
	Request *temp = new Request(i, dep, rt);
	temp->addData(d2, DataType::BOOL);
	temp->addTargetName(d1);
	return temp;
}
eeGames::Request *eeGames::create_request(const std::string &i, const std::string &dep, RequestType rt, const std::string &d1, std::string &d2)
{
	if (rt != RequestType::WRITE_DATA)
		rt = RequestType::ERROR_MISMATCH_TYPE;
	Request *temp = new Request(i, dep, rt);
	temp->addData(&d2, DataType::STRING);
	temp->addTargetName(d1);
	return temp;
}



