#include "ee_DataContainer.hpp"

bool eeGames::DataContainer::remove(const std::string &k)
{
	auto dataIterator = _data.find(k);
	if (dataIterator == _data.end())
		return false;
	_data.erase(dataIterator);
	return true;
}

bool eeGames::DataContainer::saveToFile(const std::string & dir)
{
	std::ofstream file; 
	file.open(dir, std::ios::binary);

	if (file.is_open())
	{
		for (auto pair : _data)
		{
			file.write(pair.first.c_str(), pair.first.size() + 1);
			file.write(reinterpret_cast<char*>(createByteArray(pair.second.size(), sizeof(uint8_t)).data()),
				sizeof(uint8_t));
			file.write(reinterpret_cast<char*>(pair.second.data()), pair.second.size());
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

	boost::interprocess::file_mapping fmap(dir.c_str(), boost::interprocess::read_only);
	boost::interprocess::mapped_region region(fmap, boost::interprocess::read_only);
	float *addrress = reinterpret_cast<float *>(region.get_address());
	s

	if (file.is_open())
	{
		clear(); // empty the current data container

		/*
		// write file info to buffer:
		std::vector<byte> buffer((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
		std::string temp_key;
		std::vector<byte> temp_data, temp_size;

		// parse buffer:
		int i = 0, j;
		while (i < buffer.size())
		{
			for (; buffer[i] != '\0'; i++)
				temp_key += buffer[i];
			j = ++i;
			for (; i < j + sizeof(uint8_t); i++)
				temp_size.push_back(buffer[i]);
			j = i;
			for (; i < j + *reinterpret_cast<uint8_t *>(temp_size.data()); i++)
				temp_data.push_back(buffer[i]);

			byte *temp_container = new byte[temp_data.size()];
			memcpy(temp_container, temp_data.data(), temp_data.size());

			data[temp_key] = byte_arr(temp_container, temp_data.size());

			temp_key.clear(); // clear string
			temp_data.clear(); // clear data
			temp_size.clear(); // clear size
		}
		return true;
	}
	*/
	return false;
}

void eeGames::DataContainer::clear()
{
	_data.clear();
}

