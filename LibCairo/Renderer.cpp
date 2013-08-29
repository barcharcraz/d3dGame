#include "Renderer.h"
#include <LibComponents2D/Transform.h>
namespace CairoRenderer {
	Renderer::Renderer()
		: System({typeid(Components::Transform2D)})
	{
		
	}
	void Renderer::Init() {
		
	}

}
