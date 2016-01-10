#pragma once

#include <string>

#include "ee_DataContainerEngine.hpp"
#include "ee_RequestType.hpp"

namespace eeGames
{
	class Request
	{
	private:
		uint16_t priority; // lower value has highest priority
		uint8_t ref_count;
		std::string dependency, id;
		RequestType r_type;

		// for storing data
		DataType d_type;
		std::string target_name;
		byte *data;
	public:
		Request(const std::string &i, uint16_t p, RequestType rt);
		Request(const std::string &i, const std::string &dep, RequestType rt);

		// TODO: Certain input methods do not require a name for the string (string input)
		void add_data(void *d, DataType dt);
		void add_data(byte *d)
		{
			data = d;
		}
		void add_target_name(const std::string &n)
		{
			target_name = n;
		}

		int get_int(bool *t);
		int get_int();
		float get_float(bool *t);
		float get_float();
		double get_double(bool *t);
		double get_double();
		bool get_bool(bool *t);
		bool get_bool();
		std::string get_string(bool *t);
		std::string get_string();

		RequestType get_request() const
		{
			return r_type;
		}
		uint16_t get_priority() const
		{
			return priority;
		}
		const std::string &get_dependency() const
		{
			return dependency;
		}
		const std::string &get_id() const
		{
			return id;
		}

		DataType get_data_type() const
		{
			return d_type;
		}
		const std::string &get_target_name() const
		{
			return target_name;
		}
		byte *get_data() // can't gaurentee data will remain unchanged
		{
			return data;
		}

		// angelscript
		void AddRef()
		{
			ref_count++;
		}
		void ReleaseRef()
		{
			if (--ref_count == 0)
				delete this;
		}

	};

	extern inline Request *create_request(const std::string &i, uint16_t p, RequestType rt);
	extern inline Request *create_request(const std::string &i, uint16_t p, RequestType rt, const std::string &d1);
	extern inline Request *create_request(const std::string &i, uint16_t p, RequestType rt, const std::string &d1, int *d2);
	extern inline Request *create_request(const std::string &i, uint16_t p, RequestType rt, const std::string &d1, float *d2);
	extern inline Request *create_request(const std::string &i, uint16_t p, RequestType rt, const std::string &d1, double *d2);
	extern inline Request *create_request(const std::string &i, uint16_t p, RequestType rt, const std::string &d1, bool *d2);
	extern inline Request *create_request(const std::string &i, uint16_t p, RequestType rt, const std::string &d1, std::string &d2);

	extern inline Request *create_request(const std::string &i, const std::string &dep, RequestType rt);
	extern inline Request *create_request(const std::string &i, const std::string &dep, RequestType rt, const std::string &d1);
	extern inline Request *create_request(const std::string &i, const std::string &dep, RequestType rt, const std::string &d1, int *d2);
	extern inline Request *create_request(const std::string &i, const std::string &dep, RequestType rt, const std::string &d1, float *d2);
	extern inline Request *create_request(const std::string &i, const std::string &dep, RequestType rt, const std::string &d1, double *d2);
	extern inline Request *create_request(const std::string &i, const std::string &dep, RequestType rt, const std::string &d1, bool *d2);
	extern inline Request *create_request(const std::string &i, const std::string &dep, RequestType rt, const std::string &d1, std::string &d2);
}
