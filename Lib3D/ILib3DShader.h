#pragma once
#include <d3d11.h>
#include <atlbase.h>
#include <iostream>
#include <fstream>
#include <memory>
#include "MacroUtils.h"

class ILib3DShader
{
public:
	__declspec(property(get=getShader) ) CComPtr<ID3D11DeviceChild> Shader;
	virtual CComPtr<ID3D11DeviceChild> getShader() = 0;
	virtual void readShader(LIBSTRING file) = 0;
	ILib3DShader(const CComPtr<ID3D11Device> device);
	virtual ~ILib3DShader(void);
protected:
	CComPtr<ID3D11Device> m_device;
	///-------------------------------------------------------------------------------------------------
	/// <summary>	Reads binary data from a file
	/// 			and returns it as a void pointer.
	/// 			Well actually returns it as a unique_ptr<void>
	/// 			but this is c++ bitches </summary>
	///
	/// <remarks>	Charlie, 9/19/2012. </remarks>
	///
	/// <param name="file">	The file to read, this should be a std::wstring on windows
	/// 					systems if the program has been compiled in unicode
	/// 					and a std::string if it has been compiled without
	/// 					unicode. </param>
	///
	/// <returns>	A pointer to the binary data that was in the file. </returns>
	///-------------------------------------------------------------------------------------------------

	std::unique_ptr<char> readBinaryData(LIBSTRING file);
	std::unique_ptr<char> readBinaryData(LIBSTRING file, __out std::ifstream::pos_type &size);
	LIBSTRING m_fileCurrent;
};

