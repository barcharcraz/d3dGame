#ifndef UTILS_STRINGS_H
#define UTILS_STRINGS_H
#include <string>
#include <locale>
#include <vector>
#include <cwchar>
#include <algorithm>
#include <iterator>

namespace utils {
    inline std::vector<const char*> convert_array(
                const std::vector<std::string>& array) {
        std::vector<const char*> rv;
        rv.reserve(array.size());
        for(auto& elm : array) {
            rv.push_back(elm.c_str());
        }
        return rv;
    }
    inline void ltrim(std::string * in, char delim = ' ') {
        in->erase(begin(*in), std::find_if(begin(*in), end(*in), [=](char a){
            return a != delim;
        }));
    }
    inline void rtrim(std::string * in, char delim = ' ') {
        in->erase(std::find_if(in->rbegin(), in->rend(), [=](char a) {
            return a != delim;
        }).base(), end(*in));
    }
    inline void trim(std::string* in, char delim = ' ') {
        rtrim(in, delim);
        ltrim(in, delim);
    }
	
#ifdef _WIN32
#pragma warning( push )
#pragma warning( disable:4996 )
#endif
	inline std::string narrow(const std::wstring& wstr) {
        std::mbstate_t state = std::mbstate_t();
        auto buffer = wstr.c_str();
        size_t len = 1 + std::wcsrtombs(NULL, &buffer, 0, &state);
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
        size_t len = 1 + std::mbsrtowcs(NULL, &buffer, 0, &state);
        std::vector<wchar_t> wstrbuf(len);
        std::mbsrtowcs(&wstrbuf[0], &buffer, wstrbuf.size(), &state);
        return std::wstring(wstrbuf.data());
        //again does not work on GCC because reasons
        //std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        //return converter.from_bytes(nstr);
	}
#ifdef _WIN32
#pragma warning( pop )
#endif
}


#endif
