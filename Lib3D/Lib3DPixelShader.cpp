#include "stdafx.h"
#include "Lib3DPixelShader.h"


Lib3DPixelShader::Lib3DPixelShader(CComPtr<ID3D11Device> device) : ILib3DShader(device)
{
}


Lib3DPixelShader::~Lib3DPixelShader(void)
{
}

CComPtr<ID3D11DeviceChild> Lib3DPixelShader::getShader() {
	return m_shader;
}

void Lib3DPixelShader::readShader(LIBSTRING file) {
	using namespace std;
	ifstream::pos_type size;
	unique_ptr<char> data = readBinaryData(file, size);
	
	m_device->CreatePixelShader(data.get(), (SIZE_T)size, NULL, &m_shader);
}


