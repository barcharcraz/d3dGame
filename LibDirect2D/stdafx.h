// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#ifdef LIBDIRECT2D_EXPORTS
#define LIBDIRECT2D_API __declspec(dllexport)
#else
#define LIBDIRECT2D_API __declspec(dllimport)
#endif


#pragma comment(lib, "LibDXGI.lib")
#include "targetver.h"
#include <atlbase.h>
#include <d2d1_1.h>
#include <d2d1_1helper.h>
#include <dxgi1_2.h>
#include <LibDXGI\LibDXGI.h>

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers