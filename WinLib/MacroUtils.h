#pragma once
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the WINLIB_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// WINLIB_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef WINLIB_EXPORTS
#define WINLIB_API __declspec(dllexport)
#else
#define WINLIB_API __declspec(dllimport)
#endif


#ifdef UNICODE
#define LIBSTRING std::wstring
#else
#define LIBSTRING std::string
#endif