#pragma once

#include <unordered_map>
#include <vector>
#include <fstream>
#include <string>

#include <boost\interprocess\file_mapping.hpp>
#include <boost\interprocess\mapped_region.hpp>

// Container that can store data
// No casting saftey (ex: can cast data originally an int as a float)
// Each value has a specific key in the form of a standard c++ array
// can write and load binary files

namespace eeGames
{
	typedef uint8_t byte;

	class DataContainer
	{
	private:
		std::unordered_map<std::string, std::vector<byte>> _data;

		template <typename T> // utilizes move-semantics
		std::vector<byte> createByteArray(T data, byte size) const
		{
			std::vector<byte> byteArray(size);
			for (int i = 1; i <= size; i++)
			{
				byteArray[size - i] = data % 256;
				data /= 256;
			}
			return byteArray;
		}
		template<typename T>
		void getDataFromByteArray(const std::vector<uint8_t> &byteArray, T *data, uint8_t size) const
		{
			*data = 0;
			for (int i = 0; i < size; i++)
			{
				*data = *data * 256 + byteArray[i];
			}
		}
	public:
		DataContainer() {}

		// non-copyable (for now)
		DataContainer(const DataContainer&) = delete;
		DataContainer& operator=(const DataContainer&) = delete;

		template <typename T> // utilizes move-semantics
		void addIntData(const std::string &id, T data)
		{
			_data.insert(std::make_pair(id, createByteArray(data, sizeof(T))));
		}
		template <typename T> // utilizes move-semantics
		void add_float(const std::string &id, T data)
		{
			switch (sizeof(T))
			{
			case 1:
				_data.insert(std::make_pair(id, createByteArray(*(reinterpret_cast<uint8_t*>(&data)), sizeof(uint8_t))));
				break;
			case 2:
				_data.insert(std::make_pair(id, createByteArray(*(reinterpret_cast<uint16_t*>(&data)), sizeof(uint16_t))));
				break;
			case 3:
				_data.insert(std::make_pair(id, createByteArray(*(reinterpret_cast<uint32_t*>(&data)), sizeof(uint32_t))));
				break;
			case 4:
				_data.insert(std::make_pair(id, createByteArray(*(reinterpret_cast<uint64_t*>(&data)), sizeof(uint64_t))));
				break;
			default:
				_data.insert(std::make_pair(id, createByteArray(*(reinterpret_cast<uintmax_t*>(&data)), sizeof(uintmax_t))));
				break;
			}
		}
		void add_tring(const std::string &id, const std::string &data)
		{
			// simple add an array of characters for a string
			_data.insert(std::make_pair(id, std::vector<uint8_t>(data.begin(), data.end())));
		}

		// removing elements
		bool remove(const std::string&);

		// getting elements (returns nullptr if it can't find it)
		template <typename T>
		bool get_data(const std::string &id, T *data) const
		{
			auto it = _data.find(id);
			if (it == _data.end())
				return false;

			int size = it->second.size();
			switch (size)
			{
			case 1:
				getDataFromByteArray(it->second, data, 1);
				break;
			case 2:
				getDataFromByteArray(it->second, data, 2);
				break;
			case 3:
				getDataFromByteArray(it->second, data, 3);
				break;
			case 4:
				getDataFromByteArray(it->second, data, 4);
				break;
			default:
				getDataFromByteArray(it->second, data, size);
				break;
			}
			return true;
		}

		// file I/O
		bool saveToFile(const std::string&);
		bool load_from_file(const std::string&);

		void clear();
	};
}
