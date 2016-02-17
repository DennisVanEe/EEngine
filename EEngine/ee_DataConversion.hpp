#pragma once

#include <stdint.h>
#include <vector>

namespace eeGames
{
	typedef uint8_t byte;

	// converts data to array of vectors
	template <typename T> // utilizes move-semantics
	std::vector<byte> get_byteVec(T data) 
	{
		std::vector<byte> bytes_vec(sizeof(T));
		for (int i = 1; i <= sizeof(T); i++)
		{
			bytes_vec[sizeof(T) - i] = data % 256;
			data /= 256;
		}
		return std::move(bytes_vec);
	}
	// converts vector of bytes to data
	template<typename T>
	void get_byteData(const std::vector<byte> &bytes_vec, T *data)
	{
		*data = 0;
		for (int i = 0; i < bytes_vec.size(); i++)
		{
			*data = *data * 256 + bytes_vec[i];
		}
	}
}