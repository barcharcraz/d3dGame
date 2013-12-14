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
                output << preprocess_includes(file) << '\n';
                output << "#line 0\n";
            } else {
                output << line << '\n';
            }
        }
        
        return output.str();
    }
    inline std::string load_source_file(const std::string& filename) {
        std::ifstream file(filename);
        return preprocess_includes(file);
    }
	/*
	* these functions work on strings, hence the strange self parameter
	* there /could/ be a source file class, but it would add boilerplate
	*/


	//! \brief adds a line of text to a string
	//! 	   
	//! this is essentially just an insert call.
	//!	but we append a newline if text does not have one
	//!	
	//! \param self the string to add text to, this will be
	//!        mutated but the pointer will not move
	//!	\param text the text to add
	//!	\param offset the line to add the text (Optional) default is 0
    inline void add_text(std::string* const self, std::string text, int offset = 0) {
        if(text.back() != '\n') {
            text.push_back('\n');
        }
        int insertPos = 0;
        int line = 0;
        //search for the position to insert the string
        for(insertPos = 0; line < offset; ++insertPos) {
            if((*self)[insertPos] == '\n') {
                line++;
            }
        }
        self->insert(insertPos, std::move(text));
    }

	//! \brief adds a define to self
	//!
	//!	by define we mean a string of the form #define name
	inline void add_define(std::string* const self, const std::string& name, int offset = 0) {
		add_text(self, "#define " + name, offset);
	}
	inline void add_define(std::string* const self, const std::string name, const std::string value, int offset = 0) {
		add_text(self, "#define " + name + " " + value, offset);
	}
	inline void add_defines(std::string* const self, const std::vector<std::string>& defines, int offset = 0) {
		for (auto& elm : defines) {
			add_define(self, elm, offset);
		}
	}
	inline void add_defines(std::string* const self, const std::vector<std::pair<std::string, std::string>>& defines, int offset = 0) {
		for (auto& elm : defines) {
			add_define(self, elm.first, elm.second, offset);
		}
	}
}

#endif
