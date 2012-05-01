// WinLib.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "WinLib.h"


// This is an example of an exported variable
WINLIB_API int nWinLib=0;

// This is an example of an exported function.
WINLIB_API int fnWinLib(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see WinLib.h for the class definition
CWinLib::CWinLib()
{
	return;
}
