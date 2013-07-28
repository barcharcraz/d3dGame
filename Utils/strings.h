#ifndef UTILS_STRINGS_H
#define UTILS_STRINGS_H
#include <string>
#include <codecvt>
#include <locale>

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
	inline std::string narrow(const std::wstring& wstr) {
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		return converter.to_bytes(wstr);
	}
	inline std::wstring widen(const std::string& nstr) {
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		return converter.from_bytes(nstr);
	}
}


#endif
