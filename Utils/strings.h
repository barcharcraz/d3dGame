#ifndef UTILS_STRINGS_H
#define UTILS_STRINGS_H
#include <string>
#include <locale>
#include <vector>
#include <cwchar>

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
        std::mbstate_t state = std::mbstate_t();
        auto buffer = wstr.c_str();
        int len = 1 + std::wcsrtombs(nullptr, &buffer, 0, &state);
        std::vector<char> nstrbuf(len);
        std::wcsrtombs(&nstrbuf[0], &buffer, nstrbuf.size(), &state);
        return std::string(nstrbuf.data());
        //this stuff does not work in GCC, FML
        //std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        //return converter.to_bytes(wstr);
	}
	inline std::wstring widen(const std::string& nstr) {
        std::mbstate_t state = std::mbstate_t();
        auto buffer = nstr.c_str();
        int len = 1 + std::mbsrtowcs(nullptr, &buffer, 0, &state);
        std::vector<wchar_t> wstrbuf(len);
        std::mbsrtowcs(&wstrbuf[0], &buffer, wstrbuf.size(), &state);
        return std::wstring(wstrbuf.data());
        //again does not work on GCC because reasons
        //std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        //return converter.from_bytes(nstr);
	}
}


#endif
