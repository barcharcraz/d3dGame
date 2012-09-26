#pragma once
#include "ilib3dshader.h"
#include <atlbase.h>
class Lib3DVertexShader :
	public ILib3DShader
{
public:
	virtual CComPtr<ID3D11DeviceChild> getShader();
	virtual void readShader(LIBSTRING file);
	Lib3DVertexShader(const CComPtr<ID3D11Device> device);
	~Lib3DVertexShader(void);
private:
	
	CComPtr<ID3D11VertexShader> m_shader;
};

