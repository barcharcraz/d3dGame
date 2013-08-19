
#pragma once
#include "stdafx.h"
#include "Direct2DRenderer.h"
#include <LibCommon/System.h>
#include <LibCommon/Entity.h>

namespace LibDirect2D {
	class Renderer : public LibCommon::System {
	public:
		Renderer(const Direct2DRenderer& render_arg);
		virtual void Init() override;
		virtual void Process(LibCommon::Entity* ent) override;
	private:
		const Direct2DRenderer* render;
		CComPtr<ID2D1SolidColorBrush> brush;
	};
}
