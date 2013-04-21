#pragma once
#include "stdafx.h"
#include <LibCommon/IComponent.h>
#include <LibCommon/Get.hpp>
#include <d2d1_1.h>
#include <d2d1_1helper.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include "Direct2DRenderingMessage.h"
namespace LibDirect2D {
	class Direct2DRectRenderer : public LibCommon::IComponent {
	public:
		Direct2DRectRenderer(D2D1_RECT_F rect);
	private:
		D2D1_RECT_F _mRect;
		CComPtr<ID2D1SolidColorBrush> _mpBrush;
		void HandleDraw(Direct2DRenderingMessage *message);
		void init(); //do our handler init stuff
	};
}