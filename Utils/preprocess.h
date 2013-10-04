#include "files.h"
#include "strings.h"
#include <iostream>
#ifndef UTILS_PREPROCESS_H
#define UTILS_PREPROCESS_H

namespace utils {
    //freestanding parsing functions

    inline void include_parse(std::vector<std::string>* shader_src) { 
        std::vector<std::string> includes;
        std::string compareTo = "#include ";
        for(auto& str : *shader_src) {
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
    inline void add_defines(std::vector<std::string>* shader_src, 
                     std::vector<std::string> defines) {
        for(auto& def : defines) {
            shader_src->insert(begin(*shader_src), "#define " + std::move(def));
        }
    }
    inline void preprocess(std::vector<std::string>* shader_src,
                    std::vector<std::string> defines) {
        include_parse(shader_src);
        add_defines(shader_src, std::move(defines));
    }
    inline void preprocess(std::vector<std::string>* shader_src) {
        include_parse(shader_src);
    }
}

#endif
