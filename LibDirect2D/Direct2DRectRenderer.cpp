#include "Direct2DRectRenderer.h"
using namespace LibDirect2D;

Direct2DRectRenderer::Direct2DRectRenderer(D2D1_RECT_F rect) 
	:_mRect(rect)
{
	init();
}
void Direct2DRectRenderer::init() {
	receive.connect([this](LibCommon::IMessage& msg)
	{this->HandleDraw(dynamic_cast<Direct2DRenderingMessage&>(msg));});
}
void Direct2DRectRenderer::HandleDraw(Direct2DRenderingMessage &message) {
	Eigen::Affine2f * transform;

	message.pContext->BeginDraw();
	HRESULT hr;
	if(nullptr == _mpBrush) {
		//make a new solid brush if we dont have one already
		// TODO: make this lookup for existing brushes
		hr = message.pContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &_mpBrush);
	}
	//ID2D1Factory* pTempFactory;
	//message.pContext->GetFactory(&pTempFactory);
	//ID2D1DeviceContext* test = &message.pContext;
	//message.pContext->Clear(D2D1::ColorF(D2D1::ColorF::Black));
	message.pContext->FillRectangle(_mRect, _mpBrush);
	message.pContext->EndDraw();
}