#include "stdafx.h"
#include "Direct2DBitmap.h"
namespace LibDirect2D {
	Direct2DBitmap::Direct2DBitmap(std::wstring file) 
		: filename(file) 
	{
		receive.connect<Direct2DRenderingMessage*>([this](Direct2DRenderingMessage* msg){this->HandleDraw(msg);});
		
	}
	void Direct2DBitmap::HandleDraw(Direct2DRenderingMessage *message) {
		HRESULT hr = S_OK;
		if(lazyBitmap == nullptr) {
			BitmapLoader::initialize();
			hr = BitmapLoader::LoadImageFromFile(filename, *message->pContext, &lazyBitmap);
			if(FAILED(hr)) {
				throw hr;
			}
			BitmapLoader::unInitialize();
		}
		LibCommon::Get<LibCommon::Transform2D, Eigen::Affine2f> * msg = new LibCommon::Get<LibCommon::Transform2D, Eigen::Affine2f>(this);
		this->send(msg);
		Eigen::Affine2f transform = *msg->value;
		D2D1_MATRIX_3X2_F d2dTransform = Affine2f_to_D2D1Matrix3x2f(transform);
		message->pContext->SetTransform(d2dTransform);
		message->pContext->BeginDraw();
		message->pContext->DrawImage(lazyBitmap, D2D1_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
		message->pContext->EndDraw();
	}
}