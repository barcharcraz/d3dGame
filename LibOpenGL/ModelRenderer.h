
#ifndef LIBOPENGL_MODELRENDERER_H
#define LIBOPENGL_MODELRENDERER_H
#include "stdafx.h"
#include <LibCommon/System.h>
#include <LibCommon/Entity.h>
namespace LibOpenGL {
    class ModelRenderer : public LibCommon::System {
    public:
        ModelRenderer();
        virtual void Process(LibCommon::Entity * ent) override;
	private:
		Gluint _vertexBuffer;
		
    };
}

#endif