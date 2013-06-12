#pragma once
#include "stdafx.h"
#include "Direct2DRenderingMessage.h"
#include "BitmapLoader.h"
#include "Conversions.h"
#include <LibCommon/IComponent.h>
#include <LibCommon/IMessage.h>
#include <LibCommon/Get.hpp>
#include <LibCommon/Transform2D.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
namespace LibDirect2D {
	class Direct2DBitmap : public LibCommon::IComponent {
	public:
		Direct2DBitmap(std::wstring file);
	private:
		void HandleDraw(Direct2DRenderingMessage *message);
		CComPtr<ID2D1Bitmap> lazyBitmap;
		std::wstring filename;
	};
}