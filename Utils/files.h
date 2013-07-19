#ifndef UTILS_FILES_H
#define UTILS_FILES_H

#include <memory>
#include <string>
#include <fstream>
#include <vector>
namespace utils {
	std::unique_ptr<std::vector<unsigned char>> slurpBinary(const std::string& filename) {
		std::ifstream stream(filename, std::ios::in | std::ios::binary | std::ios::ate);
		std::ifstream::pos_type size = stream.tellg();
		std::unique_ptr<std::vector<unsigned char>> buffer = std::make_unique<std::vector<unsigned char>>(size);
		stream.seekg(0, std::ios::beg);
		stream.read((char*) buffer->data(), size);
		return buffer;
	}
}

#endif