#pragma once
#include "stdafx.h"
#include "Direct3DRenderer.h"
#include <LibCommon/System.h>
#include <LibCommon/Entity.h>
#include <LibCommon/Data.h>
namespace LibDirect3D {
	class BoundingBoxRenderer : public LibCommon::System {
	public:
		BoundingBoxRenderer(const Direct3DRenderer& renderer);
		virtual void Init() override;
		virtual void PreProcess() override;
		virtual void Process(LibCommon::Entity* ent) override;
	private:
		struct res {
			CComPtr<ID3D11Buffer> vertexBuffer;
			CComPtr<ID3D11Buffer> indexBuffer;
		};
		res buffers;
		LibCommon::Transforms trans;
		const Direct3DRenderer* render;
	};
}