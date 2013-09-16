#include <LibCommon/System.h>
#include <LibCommon/Entity.h>
#ifndef LIBCAIRO_CAIRORENDERER_H
#define LIBCAIRO_CAIRORENDERER_H

namespace CairoRenderer {
	class Renderer : public LibCommon::System {
	public:
		Renderer();
		virtual void Init() override;
		virtual void Process(LibCommon::Entity* ent) override;
		
	};
}

#endif