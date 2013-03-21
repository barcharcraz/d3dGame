#pragma once
#include "IShape.h"
#include "Entity.h"
#include <Unknwn.h>
#include <vector>

namespace LibCommon {
	using namespace std;
	class Scene : IShape {
	public:
		virtual void draw(IUnknown* pContext) override;
		vector<Entity> Members;
	};
}