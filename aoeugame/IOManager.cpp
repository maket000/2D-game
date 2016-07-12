#include <fstream>
#include "IOManager.h"

static bool readFileToBuffer(std::string filepath, std::vector<char>& buffer) {
	std::ifstream file(filepath, std::ios::binary);
	if (file.fail()) {
		perror(filepath.c_str());
		return false;
	}

	file.seekg(0, std::ios::end);
	int fileSize = file.tellg();
	file.seekg(0, std::ios::beg);

	buffer.resize(fileSize);
	file.read(&buffer[0], fileSize);

	file.close();
	return true;
}