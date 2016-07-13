#pragma once

#include <vector>

namespace MKT2D {

	class IOManager
	{
	public:
		static bool readFileToBuffer(std::string filepath, std::vector<unsigned char>& buffer);

	};

}