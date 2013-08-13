#ifndef LIBPREFABS_STATICMODEL_H
#define LIBPREFABS_STATICMODEL_H
#include <LibCommon/Entity.h>
#include <LibComponents/Model.h>
#include <LibComponents/Texture.h>
namespace Prefabs {
	class StaticModel : public LibCommon::Entity {
	public:
		StaticModel(const Components::Model& mod, const Components::Texture& tex);
	};
}

#endif