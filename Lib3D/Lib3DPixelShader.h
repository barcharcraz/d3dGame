#pragma once
#include "ilib3dshader.h"
class Lib3DPixelShader :
	public ILib3DShader
{
public:
	Lib3DPixelShader(const CComPtr<ID3D11Device> device);
	virtual CComPtr<ID3D11DeviceChild> getShader();
	virtual void readShader(LIBSTRING file);
	~Lib3DPixelShader(void);
private:
	CComPtr<ID3D11PixelShader> m_shader;
};

