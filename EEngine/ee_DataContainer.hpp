#pragma once

#include <unordered_map>
#include <fstream>
#include <string>

// Container that can store data
// No casting saftey (ex: can cast data originally an int as a float)
// Each value has a specific key in the form of a standard c++ array
// can write and load binary files

namespace eeGames
{
	typedef char byte; //this will be used by Request as well for data storage

	class DataContainer
	{
	protected:
		struct byte_arr
		{
			byte_arr() {} // default constructor
			byte_arr(byte *d, unsigned int s)
			{
				data = d;
				size = s; // used during reading and writing to file
			}
			byte *data;
			unsigned int size;
		};
	private:
		std::unordered_map<std::string, byte_arr> data;
	public:
		DataContainer();
		~DataContainer(); // releases data from memory

		// non-copyable (for now)
		DataContainer(const DataContainer&) = delete;
		DataContainer& operator=(const DataContainer&) = delete;

		// adding elements
		void add_int(const std::string&, int);
		void add_float(const std::string&, float);
		void add_double(const std::string&, double);
		void add_string(const std::string&, const std::string&);
		void add_bool(const std::string &, bool);

		// removing elements
		bool remove(const std::string&);

		// getting elements (returns false if it can't find it)
		byte *get_data(const std::string&) const;

		// file I/O
		bool save_to_file(const std::string&);
		bool load_from_file(const std::string&);

		void clear();
	};
}
