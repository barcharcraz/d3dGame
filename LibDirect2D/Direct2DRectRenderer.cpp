#include "Direct2DRectRenderer.h"
using namespace LibDirect2D;

Direct2DRectRenderer::Direct2DRectRenderer(D2D1_RECT_F rect) 
	:_mRect(rect)
{
	init();
}
void Direct2DRectRenderer::init() {
	receive.connect([this](const LibCommon::IMessage& msg)
	{this->HandleDraw(dynamic_cast<const Direct2DRenderingMessage&>(msg));});
}
void Direct2DRectRenderer::HandleDraw(const Direct2DRenderingMessage &message) {
	message.pContext.BeginDraw();
	if(!_mpBrush) {
		//make a new solid brush if we dont have one already
		// TODO: make this lookup for existing brushes
		message.pContext.CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &_mpBrush);
	}
	//ID2D1Factory* pTempFactory;
	//message.pContext->GetFactory(&pTempFactory);
	//ID2D1DeviceContext* test = &message.pContext;
	message.pContext.Clear(D2D1::ColorF::ColorF(D2D1::ColorF::Red));
	message.pContext.FillRectangle(_mRect, _mpBrush);
	message.pContext.EndDraw();
}