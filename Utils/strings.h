#ifndef UTILS_STRINGS_H
#define UTILS_STRINGS_H
#include <string>
namespace utils {
	inline void trim(std::string * in) {
		std::string::iterator end = in->end();
		std::string::iterator begin = in->begin();
		//++begin;
		--end;
		if (*end == ' ') {
			in->erase(end);
			--end;
		}
		if (*begin == ' ') {
			in->erase(begin);
			++begin;
		}
		if (*begin != ' ' && *end != ' ') {
			return;
		}
		trim(in);
	}
}


#endif
