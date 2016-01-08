#include "ee_Request.hpp"

eeGames::Request::Request(const std::string &i, unsigned int p, RequestType rt) : id(i), r_type(rt), priority(p), dependency(""), d_type(DataType::NONE), data(nullptr), ref_count(1)
{
	if (p < 0)
		priority = 0;
}

eeGames::Request::Request(const std::string &i, const std::string &dep, RequestType rt) : id(i), r_type(rt), priority(-1), dependency(dep), d_type(DataType::NONE), data(nullptr), ref_count(1)
{
}

void eeGames::Request::add_data(void *d, DataType dt)
{
	d_type = dt;
	switch (dt)
	{
	case DataType::INT:
		data = new byte[sizeof(int)];
		memcpy(data, d, sizeof(int));
		break;
	case DataType::FLOAT:
		data = new byte[sizeof(float)];
		memcpy(data, d, sizeof(float));
		break;
	case DataType::DOUBLE:
		data = new byte[sizeof(double)];
		memcpy(data, d, sizeof(double));
		break;
	case DataType::BOOL:
		data = new byte[sizeof(bool)];
		memcpy(data, d, sizeof(bool));
		break;
	case DataType::STRING:
		data = new byte[reinterpret_cast<std::string*>(d)->length() + 1];
		int len = reinterpret_cast<std::string*>(d)->length() + 1;
		memcpy(data, reinterpret_cast<std::string*>(d)->c_str(), reinterpret_cast<std::string*>(d)->length() + 1);
		break;
	}
}

int eeGames::Request::get_int(bool *t)
{
	if (r_type != RequestType::READ_DATA)
	{
		*t = false;
		return 0;
	}

	if (data == nullptr)
	{
		*t = false;
		return 0;
	}

	return *reinterpret_cast<int*>(data);
}

int eeGames::Request::get_int()
{
	if (data == nullptr)
		return 0;
	return *reinterpret_cast<int*>(data);
}

float eeGames::Request::get_float(bool *t)
{
	if (r_type != RequestType::READ_DATA)
	{
		*t = false;
		return 0.f;
	}

	if (data == nullptr)
	{
		*t = false;
		return 0.f;
	}

	return *reinterpret_cast<float*>(data);
}

float eeGames::Request::get_float()
{
	if (data == nullptr)
		return 0.f;
	return *reinterpret_cast<float*>(data);
}

double eeGames::Request::get_double(bool *t)
{
	if (r_type != RequestType::READ_DATA)
	{
		*t = false;
		return 0.0;
	}

	if (data == nullptr)
	{
		*t = false;
		return 0.0;
	}

	return *reinterpret_cast<double*>(data);
}

double eeGames::Request::get_double()
{
	if (data == nullptr)
		return 0.0;
	return *reinterpret_cast<double*>(data);
}

bool eeGames::Request::get_bool(bool *t)
{
	if (r_type != RequestType::READ_DATA)
	{
		*t = false;
		return false;
	}

	if (data == nullptr)
	{
		*t = false;
		return false;
	}

	return *reinterpret_cast<bool*>(data);
}

bool eeGames::Request::get_bool()
{
	if (data == nullptr)
		return false;
	return *reinterpret_cast<bool*>(data);
}

std::string eeGames::Request::get_string(bool *t)
{
	if (r_type != RequestType::READ_DATA)
	{
		*t = false;
		return "";
	}

	if (data == nullptr)
	{
		*t = false;
		return "";
	}

	return std::string(data);
}

std::string eeGames::Request::get_string()
{
	if (data == nullptr)
		return "";
	return std::string(data);
}

// the create_request form:

eeGames::Request *eeGames::create_request(const std::string &i, int p, RequestType rt)
{
	if (rt == RequestType::CREATE_MODULE && rt == RequestType::READ_CONTAINER_FILE && rt == RequestType::READ_DATA && rt == RequestType::WRITE_CONTAINER_FILE
		&& rt == RequestType::WRITE_DATA)
		rt = RequestType::ERROR_MISMATCH_TYPE;
	return new Request(i, p, rt);
}
eeGames::Request *eeGames::create_request(const std::string &i, int p, RequestType rt, const std::string &d1)
{
	if (rt == RequestType::WRITE_DATA && rt == RequestType::CREATE_CONTAINER && rt == RequestType::REMOVE_CONTAINER
		&& rt == RequestType::SLEEP_MODULE && rt == RequestType::TERMINATE_MODULE && rt == RequestType::WAKE_MODULE)
		rt = RequestType::ERROR_MISMATCH_TYPE;
	Request *temp = new Request(i, p, rt);
	temp->add_target_name(d1);
	return temp;
}
eeGames::Request *eeGames::create_request(const std::string &i, int p, RequestType rt, const std::string &d1, int *d2)
{
	if (rt != RequestType::WRITE_DATA)
		rt = RequestType::ERROR_MISMATCH_TYPE;
	Request *temp = new Request(i, p, rt);
	temp->add_data(d2, DataType::INT);
	temp->add_target_name(d1);
	return temp;
}
eeGames::Request *eeGames::create_request(const std::string &i, int p, RequestType rt, const std::string &d1, float *d2)
{
	if (rt != RequestType::WRITE_DATA)
		rt = RequestType::ERROR_MISMATCH_TYPE;
	Request *temp = new Request(i, p, rt);
	temp->add_data(d2, DataType::FLOAT);
	temp->add_target_name(d1);
	return temp;
}
eeGames::Request *eeGames::create_request(const std::string &i, int p, RequestType rt, const std::string &d1, double *d2)
{
	if (rt != RequestType::WRITE_DATA)
		rt = RequestType::ERROR_MISMATCH_TYPE;
	Request *temp = new Request(i, p, rt);
	temp->add_data(d2, DataType::DOUBLE);
	temp->add_target_name(d1);
	return temp;
}
eeGames::Request *eeGames::create_request(const std::string &i, int p, RequestType rt, const std::string &d1, bool *d2)
{
	if (rt != RequestType::WRITE_DATA)
		rt = RequestType::ERROR_MISMATCH_TYPE;
	Request *temp = new Request(i, p, rt);
	temp->add_data(d2, DataType::BOOL);
	temp->add_target_name(d1);
	return temp;
}
eeGames::Request *eeGames::create_request(const std::string &i, int p, RequestType rt, const std::string &d1, std::string &d2)
{
	if (rt != RequestType::WRITE_DATA)
		rt = RequestType::ERROR_MISMATCH_TYPE;
	Request *temp = new Request(i, p, rt);
	temp->add_data(&d2, DataType::STRING);
	temp->add_target_name(d1);
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
	temp->add_target_name(d1);
	return temp;
}
eeGames::Request *eeGames::create_request(const std::string &i, const std::string &dep, RequestType rt, const std::string &d1, int *d2)
{
	if (rt != RequestType::WRITE_DATA)
		rt = RequestType::ERROR_MISMATCH_TYPE;
	Request *temp = new Request(i, dep, rt);
	temp->add_data(d2, DataType::INT);
	temp->add_target_name(d1);
	return temp;
}
eeGames::Request *eeGames::create_request(const std::string &i, const std::string &dep, RequestType rt, const std::string &d1, float *d2)
{
	if (rt != RequestType::WRITE_DATA)
		rt = RequestType::ERROR_MISMATCH_TYPE;
	Request *temp = new Request(i, dep, rt);
	temp->add_data(d2, DataType::FLOAT);
	temp->add_target_name(d1);
	return temp;
}
eeGames::Request *eeGames::create_request(const std::string &i, const std::string &dep, RequestType rt, const std::string &d1, double *d2)
{
	if (rt != RequestType::WRITE_DATA)
		rt = RequestType::ERROR_MISMATCH_TYPE;
	Request *temp = new Request(i, dep, rt);
	temp->add_data(d2, DataType::DOUBLE);
	temp->add_target_name(d1);
	return temp;
}
eeGames::Request *eeGames::create_request(const std::string &i, const std::string &dep, RequestType rt, const std::string &d1, bool *d2)
{
	if (rt != RequestType::WRITE_DATA)
		rt = RequestType::ERROR_MISMATCH_TYPE;
	Request *temp = new Request(i, dep, rt);
	temp->add_data(d2, DataType::BOOL);
	temp->add_target_name(d1);
	return temp;
}
eeGames::Request *eeGames::create_request(const std::string &i, const std::string &dep, RequestType rt, const std::string &d1, std::string &d2)
{
	if (rt != RequestType::WRITE_DATA)
		rt = RequestType::ERROR_MISMATCH_TYPE;
	Request *temp = new Request(i, dep, rt);
	temp->add_data(&d2, DataType::STRING);
	temp->add_target_name(d1);
	return temp;
}



