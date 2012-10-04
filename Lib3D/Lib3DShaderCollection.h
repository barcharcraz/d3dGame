#pragma once
#include "Lib3DPixelShader.h"
#include "Lib3DVertexShader.h"
#include <vector>
using namespace std;
class Lib3DShaderCollection
{
public:
	__declspec(property(get=getPS, put=setPS) ) shared_ptr<Lib3DPixelShader> PS;
	__declspec(property(get=getVS, put=setVS) ) shared_ptr<Lib3DVertexShader> VS;
	Lib3DShaderCollection(void);
	~Lib3DShaderCollection(void);
#pragma region accessors
	shared_ptr<Lib3DPixelShader> getPS();
	void setPS(shared_ptr<Lib3DPixelShader> ps);

	shared_ptr<Lib3DVertexShader> getVS();
	void setVS(shared_ptr<Lib3DVertexShader> vs);
#pragma endregion
private:
	vector<D3D11_INPUT_ELEMENT_DESC> m_inputLayoutDesc;
	shared_ptr<Lib3DPixelShader> m_ps;
	shared_ptr<Lib3DVertexShader> m_vs;
	
};

