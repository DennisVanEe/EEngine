#pragma once

#include <string>
#include <vector>

#include "ee_DataContainerEngine.hpp"
#include "ee_KeyedData.hpp"
#include "ee_RequestType.hpp"

namespace eeGames
{
	class Request
	{
	private:
		uint32_t _refCount; // used by the scripting engine

		// request info
		int32_t _priority; // lower value has highest priority (can be negative)
		std::string _dependency, _id;
		RequestType _requestType;

		KeyedData<std::string, ByteData> _data;

	public:
		Request(const std::string &id, uint16_t priority, RequestType requestType) : _id(id), _requestType(requestType), 
			_priority(priority), _dependency(""), _refCount(1) 
		{
			if (_priority < 0)
				_priority = 0;
		}
		Request(const std::string &id, const std::string &dependency, RequestType requestType) : _id(id), _requestType(requestType), 
			_priority(-1), _dependency(dependency), _refCount(1) {}

		// adding data
		template <typename T> // utilizes move-semantics
		bool add_int(const std::string &id, T data)
		{
			if (_requestType != RequestType::WRITE_DATA)
				return false;

			_data.insert(std::make_pair(id, ByteData(std::move(get_byteVec(data)), INT)));
			return true;
		}
		template <typename T> // utilizes move-semantics
		bool add_float(const std::string &id, T data)
		{
			if (_requestType != RequestType::WRITE_DATA)
				return false;

			switch (sizeof(T))
			{
			case sizeof(uint8_t):
				_data.insert(std::make_pair(id, ByteData(std::move(get_byteVec(*(reinterpret_cast<uint8_t*>(&data)))), FLOAT)));
				break;
			case sizeof(uint16_t):
				_data.insert(std::make_pair(id, ByteData(std::move(get_byteVec(*(reinterpret_cast<uint16_t*>(&data)))), FLOAT)));
				break;
			case sizeof(uint32_t):
				_data.insert(std::make_pair(id, ByteData(std::move(get_byteVec(*(reinterpret_cast<uint32_t*>(&data)))), FLOAT)));
				break;
			case sizeof(uint64_t):
				_data.insert(std::make_pair(id, ByteData(std::move(get_byteVec(*(reinterpret_cast<uint64_t*>(&data)))), FLOAT)));
				break;
			default:
				_data.insert(std::make_pair(id, ByteData(std::move(get_byteVec(*(reinterpret_cast<uintmax_t>(&data)))), FLOAT)));
				break;
			}
			return true;
		}
		bool add_string(const std::string &id, const std::string &data)
		{
			if (_requestType != RequestType::WRITE_DATA)
				return false;

			_data.insert(std::make_pair(id, ByteData(std::move(std::vector<byte>(data.begin(), data.end())), STRING)));
			return true;
		}

		// TODO: figure this one out
		void add_TargetName(const std::string &name)
		{
			_targetName = name;
		}

		// used by the data container to write data
		void add_rawData(const std::string &id, const ByteData &data)
		{
			_data.insert(std::make_pair(id, data));
		}

		// not const because scripting interface issues present themselves
		template <typename T>
		bool get_num(const std::string &id, T *data)
		{
			auto it = _data.find(id);
			if (it == _data.end())
				return false;

			if (it->second.data_type == STRING || it->second.data_type == NONE)
				return false;
			if (_requestType != RequestType::READ_DATA)
				return false;
			if (it->second.byte_vec.size() == 0)
				return false;

			switch (it->second.data_type)
			{
			case INT:
				get_byteData(it->second.byte_vec, data);
				break;
			case FLOAT:
				switch (_data.size())
				{
				case sizeof(float) :
					get_byteData(it->second.byte_vec, reinterpret_cast<uintmax_t*>(data));
					*data = *reinterpret_cast<float*>(data);
					break;
				case sizeof(double) :
					get_byteData(it->second.byte_vec, reinterpret_cast<uintmax_t*>(data));
					*data = *reinterpret_cast<double*>(data);
					break;
				}
				break;
			}
			return true;
		}
		bool get_string(const std::string &id, std::string *data)
		{
			auto it = _data.find(id);
			if (it == _data.end())
				return false;

			if (it->second.data_type != STRING)
				return false;
			if (_requestType != RequestType::READ_DATA)
				return false;
			if (it->second.byte_vec.size() == 0)
				return false;

			*data = std::string(it->second.byte_vec.begin(), it->second.byte_vec.end());
			return true;
		}

		RequestType get_request() const
		{
			return _requestType;
		}
		uint16_t get_priority() const
		{
			return _priority;
		}
		const std::string &get_dependency() const
		{
			return _dependency;
		}
		const std::string &get_ID() const
		{
			return _id;
		}

		// for looping through the data in the request
		auto begin()
		{
			return _data.begin();
		}
		auto begin() const
		{
			return _data.begin();
		}
		auto end()
		{
			return _data.end();
		}
		auto end() const
		{
			return _data.end();
		}

		// angelscript
		void AddRef()
		{
			_refCount++;
		}
		void ReleaseRef()
		{
			if (--_refCount == 0)
				delete this;
		}
	};

	extern inline Request *create_request(const std::string &i, int32_t p, RequestType rt);
	extern inline Request *create_request(const std::string &i, const std::string &dep, RequestType rt);
}
