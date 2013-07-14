#ifndef UTILS_STRINGS_H
#define UTILS_STRINGS_H
#include <string>
namespace utils {
	inline void trim(std::string * in) {
		//we dont want to try and trim anything if the
		//string is empty, inded if we get somethign like
		//'     ' we would return ''
		if (in->empty()) {
			return;
		}
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
