#include "files.h"
#include "strings.h"
#include <iostream>
#ifndef UTILS_PREPROCESS_H
#define UTILS_PREPROCESS_H

namespace utils {
    //freestanding parsing functions
    inline std::string parse_includes(const std::string& filename) {
        
    }
    class SourceFile {
    public:
        SourceFile() = default;
		explicit SourceFile(int offset_arg) : offset(offset_arg) {}
        SourceFile(std::vector<std::string> source) 
            : shader_src(std::move(source))
        {
        }
		int Offset() const {
			return offset;
		}
		void Offset(int newOffset) {
			offset = newOffset;
		}
        std::vector<const char*> cdata() const {
            return utils::convert_array(shader_src);
        }
        void include_parse() { 
            std::vector<std::string> includes;
            std::string compareTo = "#include ";
			for (auto str = begin(shader_src) + offset; str != end(shader_src); ++str) {
                if(str->compare(0, compareTo.size(), compareTo) == 0) {
                    //get the contents of the other file
                    std::string filename = str->substr(compareTo.size(), str->size());
                    filename.erase(find(begin(filename), end(filename), '\n'));
                    //first we trim off the spaces than we trim off the "s, we do not
                    //support include paths
                    trim(&filename);
                    trim(&filename, '"');
                    std::cerr << filename << std::endl;
                    *str = utils::slurpText(filename);
                }
            }
        }
        void add_text(std::string text) {
			if (text.back() != '\n') {
				text.push_back('\n');
			}
            shader_src.insert(begin(shader_src) + offset, std::move(text));
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
        std::vector<std::string> shader_src;
		int offset = 0;
    };
}

#endif
