#ifndef UTILS_FILES_H
#define UTILS_FILES_H

#include <memory>
#include <string>
#include <fstream>
#include <vector>
#include <exception>
namespace utils {
	inline std::vector<unsigned char> slurpBinary(const std::string& filename) {
		std::ifstream stream;
		stream.exceptions(std::ifstream::badbit | std::ifstream::failbit);
		stream.open(filename, std::ios::in | std::ios::binary | std::ios::ate);
		std::ifstream::pos_type size = stream.tellg();
		std::vector<unsigned char> buffer(size);
		stream.seekg(0, std::ios::beg);
		stream.read((char*) buffer.data(), size);
		return buffer;
	}
	inline std::string getFileExtension(const std::string& filename) {
		using namespace std;
		auto idx = filename.rfind('.');
		if (idx != string::npos) {
			return filename.substr(idx + 1);
		}
		return "";
	}
	inline bool fileExists(const std::string& filename) {
		std::ifstream file(filename);
		return file.is_open();
	}
}

#endif