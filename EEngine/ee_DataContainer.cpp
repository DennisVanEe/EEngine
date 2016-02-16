#include "ee_DataContainer.hpp"

bool eeGames::DataContainer::remove(const std::string &k)
{
	auto dataIterator = _data.find(k);
	if (dataIterator == _data.end())
		return false;
	_data.erase(dataIterator);
	return true;
}

bool eeGames::DataContainer::save_to_file(const std::string & dir)
{
	std::ofstream file; 
	file.open(dir, std::ios::binary);

	if (file.is_open())
	{
		for (auto pair : _data)
		{
			file.write(pair.first.c_str(), pair.first.size() + 1);
			file.write(reinterpret_cast<char*>(get_byteVec(pair.second.byte_vec.size()).data()),
				sizeof(size_t));
			file.write(reinterpret_cast<char*>(get_byteVec(pair.second.data_type).data()),
				sizeof(uint8_t));
			file.write(reinterpret_cast<char*>(pair.second.byte_vec.data()), pair.second.byte_vec.size());
		}
		return true;
	}
	return false;
}

// TODO: Finish this
bool eeGames::DataContainer::load_from_file(const std::string & dir)
{
	std::ifstream file;
	file.open(dir, std::ios::binary);

	if (file.is_open())
	{
		clear(); // empty the current data container

		// write file info to buffer:
		std::vector<byte> buffer((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
		std::vector<byte> temp_size, temp_data, temp_type;
		std::string temp_key;
		size_t num;
		uint8_t type;

		// parse buffer:
		int i = 0, j;
		while (i < buffer.size())
		{
			for (; buffer[i] != '\0'; i++)
				temp_key += buffer[i];
			j = ++i;

			temp_size.reserve(sizeof(size_t)); // prepare for addition of memory
			for (; i < j + sizeof(size_t); i++)
				temp_size.push_back(buffer[i]);
			j = i;

			temp_type.reserve(sizeof(uint8_t));
			for (; i < j + sizeof(uint8_t); i++)
				temp_type.push_back(buffer[i]);
			j = i;

			get_byteData(temp_size, &num);
			for (; i < j + num; i++)
				temp_data.push_back(buffer[i]);

			get_byteData(temp_type, &type);
			_data[temp_key] = ByteData(std::move(temp_data), type);

			temp_key.clear(); // clear string
			temp_data.clear(); // clear data
			temp_size.clear(); // clear size
		}
		return true;
	}
	return false;
}

void eeGames::DataContainer::clear()
{
	_data.clear();
}

