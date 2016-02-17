#pragma once

#include <string>
#include <vector>

#include "ee_DataContainerEngine.hpp"
#include "ee_RequestType.hpp"

namespace eeGames
{
	class Request
	{
	private:
		uint32_t _refCount;

		// request info
		int32_t _priority; // lower value has highest priority
		std::string _dependency, _id;
		RequestType _requestType;

		// data storage
		uint8_t _dataType;
		std::string _targetName;
		std::vector<uint8_t> _data;
	public:
		Request(const std::string &id, uint16_t priority, RequestType requestType) : _id(id), _requestType(requestType), 
			_priority(priority), _dependency(""), _dataType(NONE), _refCount(1) 
		{
			if (_priority < 0)
				_priority = 0;
		}
		Request(const std::string &id, const std::string &dependency, RequestType requestType) : _id(id), _requestType(requestType), 
			_priority(-1), _dependency(dependency), _dataType(NONE), _refCount(1) {}

		// TODO: no point in using double move semantics?
		template <typename T> // utilizes move-semantics
		void add_int(const std::string &id, T data)
		{
			_targetName = id;
			_dataType = INT;
			_data = std::move(get_byteVec(data));

		}
		template <typename T> // utilizes move-semantics
		void add_float(const std::string &id, T data)
		{
			_targetName = id;
			_dataType = FLOAT;
			switch (sizeof(T))
			{
			case sizeof(uint8_t) :
				_data = std::move(get_byteVec(*(reinterpret_cast<uint8_t*>(&data))));
				break;
			case sizeof(uint16_t) :
				_data = std::move(get_byteVec(*(reinterpret_cast<uint16_t*>(&data))));
				break;
			case sizeof(uint32_t) :
				_data = std::move(get_byteVec(*(reinterpret_cast<uint32_t*>(&data))));
				break;
			case sizeof(uint64_t) :
				_data = std::move(get_byteVec(*(reinterpret_cast<uint64_t*>(&data))));
				break;
			default:
				_data = std::move(get_byteVec(*(reinterpret_cast<uintmax_t*>(&data))));
				break;
			}
		}
		void add_string(const std::string &id, const std::string &data)
		{
			_targetName = id;
			_dataType = STRING;
			_data = std::move(std::vector<byte>(data.begin(), data.end()));
		}

		template <typename T>
		bool get_data(const std::string &id, T *data) const
		{
			if (_dataType == STRING || _dataType == NONE)
				return false;

			switch (dataType)
			{
			case INT:
				get_byteData(_data, data);
				break;
			case FLOAT:
				switch (_data.size())
				{
				case sizeof(float) :
					get_byteData(_data, reinterpret_cast<uintmax_t*>(data));
					*data = *reinterpret_cast<float*>(data);
					break;
				case sizeof(double) :
					get_byteData(_data, reinterpret_cast<uintmax_t*>(data));
					*data = *reinterpret_cast<double*>(data);
					break;
				}
				break;
			}
			return true;
		}
		bool get_data(const std::string &id, std::string *data) const
		{
			if (_dataType != STRING)
				return false;
			*data = std::string(_data.begin(), _data.end());
			return true;
		}

		RequestType getRequest() const
		{
			return _requestType;
		}
		uint16_t getPriority() const
		{
			return _priority;
		}
		const std::string &getDependency() const
		{
			return _dependency;
		}
		const std::string &getID() const
		{
			return _id;
		}

		uint8_t getDataType() const
		{
			return _dataType;
		}
		const std::string &getTargetName() const
		{
			return _targetName;
		}
		std::vector<byte> &getData() // can't gaurentee data will remain unchanged
		{
			return _data;
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

	extern inline Request *create_request(const std::string &i, uint16_t p, RequestType rt);
	extern inline Request *create_request(const std::string &i, const std::string &dep, RequestType rt);
}
