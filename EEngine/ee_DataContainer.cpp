#include "ee_DataContainer.hpp"

eeGames::DataContainer::DataContainer() {}

eeGames::DataContainer::~DataContainer()
{
	for (std::pair<std::string, byte_arr> pair : data)
		delete pair.second.data;
}

void eeGames::DataContainer::add_int(const std::string &k, int d)
{
	byte *tmp = new byte[sizeof(d)];
	memcpy(tmp, &d, sizeof(d));
	data[k] = byte_arr(tmp, sizeof(d));
}

void eeGames::DataContainer::add_float(const std::string &k, float d)
{
	byte *tmp = new byte[sizeof(d)];
	memcpy(tmp, &d, sizeof(d));
	data[k] = byte_arr(tmp, sizeof(d));
}

void eeGames::DataContainer::add_double(const std::string &k, double d)
{
	byte *tmp = new byte[sizeof(d)];
	memcpy(tmp, &d, sizeof(d));
	data[k] = byte_arr(tmp, sizeof(d));
}

void eeGames::DataContainer::add_string(const std::string &k, const std::string &d)
{
	byte *tmp = new byte[d.length() + 1];
	memcpy(tmp, d.c_str(), d.length() + 1);
	data[k] = byte_arr(tmp, d.length() + 1);
}

void eeGames::DataContainer::add_bool(const std::string &k, bool d)
{
	byte *tmp = new byte[sizeof(d)];
	memcpy(tmp, &d, sizeof(d));
	data[k] = byte_arr(tmp, sizeof(d));
}

eeGames::byte *eeGames::DataContainer::get_data(const std::string &k) const
{
	auto it = data.find(k);
	if (it == data.end())
		return nullptr;
	byte *temp = new byte[it->second.size];
	memcpy(temp, it->second.data, it->second.size);
	return temp;
}

bool eeGames::DataContainer::remove(const std::string &k)
{
	if (!data.count(k))
		return false;
	delete data.at(k).data;
	data.erase(k);
	return true;
}

bool eeGames::DataContainer::save_to_file(const std::string & dir)
{
	std::ofstream file; 
	file.open(dir, std::ios::binary);

	if (file.is_open())
	{
		for (std::pair<std::string, byte_arr> pair : data)
		{
			file.write(pair.first.c_str(), pair.first.size() + 1);
			file.write(reinterpret_cast<const byte*>(&pair.second.size), sizeof(pair.second.size));
			file.write(pair.second.data, pair.second.size);
		}
		return true;
	}
	return false;
}

bool eeGames::DataContainer::load_from_file(const std::string & dir)
{
	std::ifstream file;
	file.open(dir, std::ios::binary);

	if (file.is_open())
	{
		clear(); // empty the current data container

		// write file info to buffer:
		std::vector<byte> buffer((std::istreambuf_iterator<byte>(file)), (std::istreambuf_iterator<byte>()));
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
	return false;
}

void eeGames::DataContainer::clear()
{
	data.clear();
}

