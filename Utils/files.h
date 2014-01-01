#ifndef UTILS_FILES_H
#define UTILS_FILES_H

#include <memory>
#include <string>
#include <fstream>
#include <vector>
#include <exception>
#include "exceptions.h"
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
	inline std::string slurpText(const std::string& filename) {
		std::ifstream file(filename);
		if(!file.is_open()) {
			throw utils::not_found_error("file " + filename + " was not found");
		}
		std::string rv;
		file.seekg(0, std::ios::end);
		rv.reserve(file.tellg());
		file.seekg(0, std::ios::beg);
		rv.assign((std::istreambuf_iterator<char>(file)),
				  (std::istreambuf_iterator<char>()));
		return rv;
	}
    inline std::vector<std::string> slurpByLines(const std::string& filename) {
        std::ifstream file(filename);
        if(!file.is_open()) {
            throw utils::file_not_found_error(filename);
        }
        std::vector<std::string> rv;
        std::string next = "";
        while(file) {
            std::getline(file, next);
            next += '\n';
            rv.push_back(std::move(next));
        }
        rv.shrink_to_fit();
        return rv;
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
    //! \brief returns a string that is filename with the extension extension
    //! if filename already has the correct extension than this function returns
    //! that. If filename has a different extension an exception is raised, 
    //! if filename has no extension than the new one is appended
    inline std::string fixupExtensionInternal(std::string filename, std::string extension, bool optional) {
        if (getFileExtension(filename) == "") {
            return filename + "." + extension;
        } else if (getFileExtension(filename) == extension) {
            return filename;
        } else if(optional){
            return filename;
        } else {
            throw utils::precondition_error("filename extension is wrong");
        }
    }
    inline std::string fixupExtensionOptional(std::string filename, std::string extension) {
        return fixupExtensionInternal(filename, extension, true);
    }
    inline std::string fixupExtension(std::string filename, std::string extension) {
        return fixupExtensionInternal(filename, extension, false);
    }


}

#endif
