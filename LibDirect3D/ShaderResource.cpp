#include "ShaderResource.h"
#include "Buffers.h"
#include <stdexcept>
namespace LibDirect3D {
	CComPtr<ID3D11ShaderResourceView> createStructuredBufferView(ID3D11Device* pDev, ID3D11Buffer* buffer, unsigned int numElm) {
		CComPtr<ID3D11ShaderResourceView> retval;
		D3D11_SHADER_RESOURCE_VIEW_DESC desc;
		desc.Format = DXGI_FORMAT_UNKNOWN;
		desc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
		desc.Buffer.ElementOffset = 0;
		desc.Buffer.NumElements = numElm;
		HRESULT hr = S_OK;
		hr = pDev->CreateShaderResourceView(buffer, &desc, &retval);
		if (FAILED(hr)) {
			throw std::system_error(hr, std::system_category());
		}
		return retval;
	}
	CComPtr<ID3D11ShaderResourceView> createStructuredBufferView(ID3D11Device* pDev, const void* data, size_t structSize, size_t numElm) {
		CComPtr<ID3D11Buffer> structBuffer = createStructuredBuffer(pDev, data, structSize, numElm);
		return createStructuredBufferView(pDev, structBuffer, numElm);
	}
}