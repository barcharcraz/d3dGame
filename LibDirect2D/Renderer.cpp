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
		hr = render->getContext()->CreateSolidColorBrush(D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f), &brush);
		if (FAILED(hr)) {
			throw std::system_error(hr, std::system_category());
		}
	}
	void Renderer::Init() {
		
	}
	void Renderer::Process(LibCommon::Entity* ent) {
		auto transform = ent->Get<Components::Transform2D>();
		auto lines = ent->GetAll<Components::Line>();
		auto circles = ent->GetAll<Components::Circle>();
		auto rectangles = ent->GetAll<Components::Rectangle>();
		auto context = render->getContext();
		context->SetTransform(Affine2f_to_D2D1Matrix3x2f(transform->transform));
		context->BeginDraw();
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
			context->DrawEllipse(elm, brush);
		}
		for (auto rectangle : rectangles) {
			D2D1_RECT_F rect = RectConversion(*rectangle);
			context->DrawRectangle(rect, brush);
		}
		context->EndDraw();
	}
}