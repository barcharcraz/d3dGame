#include "stdafx.h"
#include "ILib3DShader.h"


ILib3DShader::ILib3DShader(const CComPtr<ID3D11Device> device)
{
	m_device = device;
}


ILib3DShader::~ILib3DShader(void)
{
}

std::unique_ptr<char> ILib3DShader::readBinaryData(LIBSTRING file) {
	std::ifstream::pos_type p;
	return readBinaryData(file, p);
}

///-------------------------------------------------------------------------------------------------
/// <summary>	Reads binary data from a 
/// 			file and returns a char pointer to that data.
/// 			Note that this is not a string it is a pointer to binary data. </summary>
///
/// <remarks>	Charlie, 10/4/2012. </remarks>
///
/// <param name="file">	The file </param>
/// <param name="size">	[in,out] The size, pass someting in if you want to know the size of the
/// 					binary data. </param>
///
/// <returns>	 </returns>
///-------------------------------------------------------------------------------------------------

std::unique_ptr<char> ILib3DShader::readBinaryData(LIBSTRING file, __out std::ifstream::pos_type &size) {
	std::ifstream binFile;
	binFile.open(file.c_str(), std::ios::in | std::ios::binary | std::ios::ate);
	size = binFile.tellg();
	std::unique_ptr<char> data(new char[size]);
	
	binFile.seekg(0,std::ios::beg);
	binFile.read(data.get(),size);
	m_fileCurrent = file;
	binFile.close();
	return data;
	

}
