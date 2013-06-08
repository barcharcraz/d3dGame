// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the LIBDXGI_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// LIBDXGI_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#include <atlbase.h>
#ifdef _DEBUG
#include <initguid.h>
#include <dxgidebug.h>
#endif
#ifdef LIBDXGI_EXPORTS
#define LIBDXGI_API __declspec(dllexport)
#else
#define LIBDXGI_API __declspec(dllimport)
#endif

namespace LibDXGI {
	DXGI_SWAP_CHAIN_DESC1 GetDefaultSwapChain();
	CComPtr<IDXGISwapChain1> CreateSwapChain(IDXGIDevice* pDevice, HWND target);
	CComPtr<IDXGIFactory2> GetFactory(IDXGIDevice* pDevice);
#ifdef _DEBUG
	CComPtr<IDXGIDebug> getDebugInterface();
#endif
}
