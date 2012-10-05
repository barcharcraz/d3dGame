#pragma once

#ifdef _WINDLL
#ifdef LIB3D_EXPORTS
#define LIB3D_API __declspec(dllexport)
#else
#define LIB3D_API __declspec(dllimport)
#endif
#else
#define LIB3D_API
#endif


#ifdef UNICODE
#define LIBSTRING std::wstring
#else
#define LIBSTRING std::string
#endif