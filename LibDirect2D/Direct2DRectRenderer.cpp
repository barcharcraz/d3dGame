#include "stdafx.h"
#include "Direct2DRectRenderer.h"
#include <LibCommon/Marked.hpp>
#include <LibCommon/Markers.h>
using namespace LibDirect2D;

Direct2DRectRenderer::Direct2DRectRenderer(D2D1_RECT_F rect) 
	:_mRect(rect)
{
	init();
}
void Direct2DRectRenderer::init() {
	receive.connect<Direct2DRenderingMessage *>([this](Direct2DRenderingMessage* msg){this->HandleDraw(msg);});
	
}
void Direct2DRectRenderer::HandleDraw(Direct2DRenderingMessage *message) {
	using namespace LibCommon;
	auto msg = std::make_unique<Marked<Tags::Transform, Get<Eigen::Affine2f> >>(this);
	this->send(msg.get());
	Eigen::Affine2f transform = *msg->value;
	D2D1_MATRIX_3X2_F d2dTransform = Affine2f_to_D2D1Matrix3x2f(transform);
	HRESULT hr;
	if(nullptr == _mpBrush) {
		//make a new solid brush if we dont have one already
		// TODO: make this lookup for existing brushes
		hr = message->pContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &_mpBrush);
	}
	message->pContext->SetTransform(d2dTransform);
	message->pContext->BeginDraw();
	//ID2D1Factory* pTempFactory;
	//message.pContext->GetFactory(&pTempFactory);
	//ID2D1DeviceContext* test = &message.pContext;
	//message->pContext->Clear(D2D1::ColorF(D2D1::ColorF::Red));
	message->pContext->FillRectangle(_mRect, _mpBrush);
	message->pContext->EndDraw();
}