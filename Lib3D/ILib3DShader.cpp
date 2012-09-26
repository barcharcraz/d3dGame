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

std::unique_ptr<char> ILib3DShader::readBinaryData(LIBSTRING file, __out std::ifstream::pos_type &size) {
	std::ifstream binFile;
	binFile.open(file.c_str(), std::ios::in | std::ios::binary | std::ios::ate);
	size = binFile.tellg();
	std::unique_ptr<char> data(new char[size]);
	
	binFile.seekg(0,std::ios::beg);
	binFile.read(data.get(),size);
	m_fileCurrent = file;
	return data;
	

}
