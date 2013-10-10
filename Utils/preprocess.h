#include "files.h"
#include "strings.h"
#include <iostream>
#ifndef UTILS_PREPROCESS_H
#define UTILS_PREPROCESS_H

namespace utils {
    //freestanding parsing functions

    class SourceFile {
    public:
        SourceFile() = default;
        SourceFile(std::vector<std::string> source) 
            : shader_src(std::move(source))
        {
            include_parse();
        }
        std::vector<const char*> cdata() const {
            return utils::convert_array(shader_src);
        }
        void include_parse() { 
            std::vector<std::string> includes;
            std::string compareTo = "#include ";
            for(auto& str : shader_src) {
                if(str.compare(0, compareTo.size(), compareTo) == 0) {
                    //get the contents of the other file
                    std::string filename = str.substr(compareTo.size(), str.size());
                    filename.erase(find(begin(filename), end(filename), '\n'));
                    //first we trim off the spaces than we trim off the "s, we do not
                    //support include paths
                    trim(&filename);
                    trim(&filename, '"');
                    std::cerr << filename << std::endl;
                    str = utils::slurpText(filename);
                }
            }
        }
        void add_text(std::string text) {
            shader_src.insert(begin(shader_src), std::move(text));
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
    };
}

#endif
