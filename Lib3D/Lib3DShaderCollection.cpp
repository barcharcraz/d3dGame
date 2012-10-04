#include "StdAfx.h"
#include "Lib3DShaderCollection.h"

Lib3DShaderCollection::Lib3DShaderCollection(void)
{
	D3D11_INPUT_ELEMENT_DESC def
	m_inputLayoutDesc.push_back();
}


Lib3DShaderCollection::~Lib3DShaderCollection(void)
{
}

#pragma region accessors
shared_ptr<Lib3DPixelShader> Lib3DShaderCollection::getPS()
{
	return m_ps;
}
void Lib3DShaderCollection::setPS(shared_ptr<Lib3DPixelShader> ps)
{
	m_ps = ps;
}

shared_ptr<Lib3DVertexShader> Lib3DShaderCollection::getVS()
{
	return m_vs;
}
void Lib3DShaderCollection::setVS(shared_ptr<Lib3DVertexShader> vs)
{
	m_vs = vs;
}
#pragma endregion