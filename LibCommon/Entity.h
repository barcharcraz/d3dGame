#pragma once
#include "IShape.h"
#include "IComponent.h"
#include <Unknwn.h>
#include <vector>

namespace LibCommon {
	using namespace std;
	class Entity : IShape {
	public:
		virtual void draw(IUnknown* pContext) override;
		vector<IComponent> Components;
	private:

	};
}