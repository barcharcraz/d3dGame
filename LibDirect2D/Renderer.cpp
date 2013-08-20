#include "Renderer.h"
#include "Conversions.h"
#include <stdexcept>
#include <LibComponents2D/Transform.h>
#include <LibComponents2D/Line.h>
#include <LibComponents2D/Circle.h>
#include <LibComponents2D/Rectangle.h>
namespace LibDirect2D {
	Renderer::Renderer(const Direct2DRenderer& render_arg)
		: System({ typeid(Components::Transform2D) }), render(&render_arg)
	{
		HRESULT hr = S_OK;
		hr = render->getContext()->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &brush);
		if (FAILED(hr)) {
			throw std::system_error(hr, std::system_category());
		}
		priority = LibCommon::Priority::HIGH;
	}
	void Renderer::Init() {
		
	}
	void Renderer::Process(LibCommon::Entity* ent) {
		HRESULT hr = S_OK;
		auto transform = ent->Get<Components::Transform2D>();
		auto lines = ent->GetAll<Components::Line>();
		auto circles = ent->GetAll<Components::Circle>();
		auto rectangles = ent->GetAll<Components::Rectangle>();
		auto context = render->getContext();
		D2D1_TAG t1 = 0;
		D2D1_TAG t2 = 0;
		context->BeginDraw();
		render->SetRenderTarget();
		context->SetTransform(Affine2f_to_D2D1Matrix3x2f(transform->transform) * render->GetProjection());
		for (auto line : lines) {
			D2D1_POINT_2F a;
			D2D1_POINT_2F b;
			a.x = line->a.x();
			a.y = line->a.y();
			context->DrawLine(a, b, brush);
		}
		for (auto circle : circles) {
			D2D1_ELLIPSE elm;
			elm.point = PointConversion( circle->center );
			elm.radiusX = circle->radius;
			elm.radiusY = circle->radius;
			context->FillEllipse(elm, brush);
		}
		for (auto rectangle : rectangles) {
			D2D1_RECT_F rect = RectConversion(*rectangle);
			context->DrawRectangle(rect, brush);
		}
		hr = context->EndDraw(&t1, &t2);
		if (FAILED(hr)) {
			throw std::system_error(hr, std::system_category());
		}
	}
}