#include "files.h"
#include "strings.h"
#include <iostream>
#include <istream>
#include <sstream>
#include <fstream>
#ifndef UTILS_PREPROCESS_H
#define UTILS_PREPROCESS_H

namespace utils {
    //freestanding parsing functions
    inline std::string preprocess_includes(std::istream& input) {
        std::ostringstream output;
        std::string compareTo = "#include ";
        std::string line = "";
        while(std::getline(input, line)) {
            if(line.compare(0, compareTo.size(), compareTo) == 0) {
                std::string filename = line.substr(compareTo.size(), line.size());
                trim(&filename);
                trim(&filename, '"');
                std::cerr << filename << std::endl;
                std::ifstream file{filename};
                output << preprocess_includes(file);
            }
        }
        return output.str();
    }
    inline std::string load_source_file(const std::string& filename) {
        std::ifstream file(filename);
        return preprocess_includes(file);
    }
    inline void add_text(std::string* const self, std::string text, int offset) {
        if(text.back() != '\n') {
            text.push_back('\n');
        }
        self->insert(offset, std::move(text));
    }
    class SourceFile {
    public:
        SourceFile() = default;
		explicit SourceFile(int offset_arg) : offset(offset_arg) {}
        SourceFile(std::string source)
        {
            std::stringstream instr(source);
            shader_src = preprocess_includes(instr);
        }
		int Offset() const {
			return offset;
		}
		void Offset(int newOffset) {
			offset = newOffset;
		}
        const char* cdata() const {
            return shader_src.c_str();
        }
        void add_text(std::string text) {
			if (text.back() != '\n') {
				text.push_back('\n');
			}
            shader_src.insert(offset, std::move(text));
        }
        void add_define(std::string name) {
            add_text("#define " + name);
        }
        void add_define(std::string name, std::string value) {
            add_text("#define " + name + " " + value);
        }
        void add_defines(std::vector<std::pair<std::string, std::string>> defines) {
            for(auto& def : defines) {
                add_define(def.first, def.second);
            }
        }
        void add_defines(std::vector<std::string> defines) {
            for(auto& def : defines) {
                add_define(def);
            }
        }
    private:
        std::string shader_src;
		int offset = 0;
    };
}

#endif
