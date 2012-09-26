#include "stdafx.h"
#include "Lib3DVertexShader.h"


Lib3DVertexShader::Lib3DVertexShader(const CComPtr<ID3D11Device> device) : ILib3DShader(device)
{
}


Lib3DVertexShader::~Lib3DVertexShader(void)
{
}

CComPtr<ID3D11DeviceChild> Lib3DVertexShader::getShader() {
	return m_shader;
}
void Lib3DVertexShader::readShader(LIBSTRING file) {
	using namespace std;
	std::ifstream::pos_type size;
	unique_ptr<char> data = readBinaryData(file, size);
	
	m_device->CreateVertexShader(data.get(), (SIZE_T)size, NULL, &m_shader);


}
