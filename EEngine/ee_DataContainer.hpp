#pragma once

#include <vector>
#include <fstream>
#include <string>

#include "ee_DataConversion.hpp"
#include "ee_KeyedData.hpp"

// Container that can store data
// No casting saftey (ex: can cast data originally an int as a float)
// Each value has a specific key in the form of a standard c++ array
// can write and load binary files

namespace eeGames
{
    #define NONE 0
	#define INT 1
	#define FLOAT 2
	#define STRING 3

	class DataContainer
	{
	private:
		struct ByteData
		{
			std::vector<byte> byte_vec;
			uint8_t data_type;
			ByteData(std::vector<byte> b_vec, uint8_t d_type) : byte_vec(std::move(b_vec)), data_type(d_type) {}
			ByteData() {}
		};
		KeyedData<std::string, ByteData> _data;

	public:
		DataContainer() {}

		// non-copyable (for now)
		DataContainer(const DataContainer&) = delete;
		DataContainer& operator=(const DataContainer&) = delete;

		template <typename T> // utilizes move-semantics
		void add_int(const std::string &id, T data)
		{
			_data.insert(std::make_pair(id, ByteData(get_byteVec(data), INT)));
		}
		template <typename T> // utilizes move-semantics
		void add_float(const std::string &id, T data)
		{
			switch (sizeof(T))
			{
			case sizeof(uint8_t):
				_data.insert(std::make_pair(id, ByteData(get_byteVec(*(reinterpret_cast<uint8_t*>(&data))), FLOAT)));
				break;
			case sizeof(uint16_t):
				_data.insert(std::make_pair(id, ByteData(get_byteVec(*(reinterpret_cast<uint16_t*>(&data))), FLOAT)));
				break;
			case sizeof(uint32_t):
				_data.insert(std::make_pair(id, ByteData(get_byteVec(*(reinterpret_cast<uint32_t*>(&data))), FLOAT)));
				break;
			case sizeof(uint64_t):
				_data.insert(std::make_pair(id, ByteData(get_byteVec(*(reinterpret_cast<uint64_t*>(&data))), FLOAT)));
				break;
			default:
				_data.insert(std::make_pair(id, ByteData(get_byteVec(*(reinterpret_cast<uintmax_t*>(&data))), FLOAT)));
				break;
			}
		}
		void add_string(const std::string &id, const std::string &data)
		{
			// simple add an array of characters for a string
			_data.insert(std::make_pair(id, ByteData(std::vector<byte>(data.begin(), data.end()), STRING)));
		}

		template <typename T>
		bool get_num(const std::string &id, T *data) const
		{
			auto it = _data.find(id);
			if (it == _data.end())
				return false;
			else if (it->second.data_type == STRING)
				return false;

			switch (it->second.data_type)
			{
			case INT:
				get_byteData(it->second.byte_vec, data);
				break;
			case FLOAT:
				switch (it->second.byte_vec.size())
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
		bool get_string(const std::string &id, std::string *data) const
		{
			auto it = _data.find(id);
			if (it == _data.end())
				return false;
			else if (it->second.data_type != STRING)
				return false;

			*data = std::string(it->second.byte_vec.begin(), it->second.byte_vec.end());
			return true;
		}

		// file I/O
		bool save_to_file(const std::string&);
		bool load_from_file(const std::string&);

		void clear();
		bool remove(const std::string&);
	};
}
