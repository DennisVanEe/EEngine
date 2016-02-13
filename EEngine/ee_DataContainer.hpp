#pragma once

#include <unordered_map>
#include <vector>
#include <fstream>
#include <string>

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
		std::unordered_map<std::string, std::vector<byte>> _m_data;

		template <typename dataType> // utilizes move-semantics
		std::vector<byte> createByteArray(dataType _p_data, byte _p_size) const
		{
			std::vector<byte> byteArray(_p_size);
			for (int i = 1; i <= _p_size; i++)
			{
				byteArray[sizeof(x) - i] = x % 256;
				x /= 256;
			}
			return byteArray;
		}
		template<typename dataType>
		void getDataFromByteArray(const std::vector<uint8_t> &byteArray, dataType *_p_data, uint8_t _p_size) const
		{
			*_p_data = 0;
			for (int i = 0; i < _p_size; i++)
			{
				*_p_data = *_p_data * 256 + byteArray[i];
			}
		}
	public:
		DataContainer() {}

		// non-copyable (for now)
		DataContainer(const DataContainer&) = delete;
		DataContainer& operator=(const DataContainer&) = delete;

		template <typename dataType> // utilizes move-semantics
		void addIntData(const std::string &_p_id, dataType _p_data)
		{
			_m_data.insert(std::make_pair(_p_id, createByteArray(_p_datat, sizeof(dataType)));
		}
		template <typename dataType> // utilizes move-semantics
		void addFloatData(const std::string &_p_id, dataType _p_data)
		{
			if (sizeof(dataType) <= 1)
				_m_data.insert(std::make_pair(_p_id, createByteArray(*(reinterpret_cast<uint8_t*>(&_p_data)), sizeof(uint8_t)));
			else if (sizeof(dataType) <= 2)
				_m_data.insert(std::make_pair(_p_id, createByteArray(*(reinterpret_cast<uint16_t*>(&_p_data)), sizeof(uint16_t)));
			else if (sizeof(dataType) <= 3)
				_m_data.insert(std::make_pair(_p_id, createByteArray(*(reinterpret_cast<uint32_t*>(&_p_data)), sizeof(uint32_t)));
			else if (sizeof(dataType) <= 4)
				_m_data.insert(std::make_pair(_p_id, createByteArray(*(reinterpret_cast<uint64_t*>(&_p_data)), sizeof(uint64_t)));
			else // if it is so big, just use the largest one 
				_m_data.insert(std::make_pair(_p_id, createByteArray(*(reinterpret_cast<uintmax_t*>(&_p_data)), sizeof(uintmax_t)));
		}
		void addStringData(const std::string &_p_id, const std::string &_p_name)
		{
			// simple add an array of characters for a string
			_m_data.insert(std::make_pair(_p_id, std::vector<uint8_t>(_p_name.begin(), _p_name.end())));
		}

		// removing elements
		bool remove(const std::string&);

		// getting elements (returns nullptr if it can't find it)
		byte *get_data(const std::string&) const;

		// file I/O
		bool saveToFile(const std::string&);
		bool load_from_file(const std::string&);

		void clear();
	};
}
