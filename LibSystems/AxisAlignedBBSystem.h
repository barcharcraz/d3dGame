#ifndef LIBSYSTEMS_AXISALIGNEDBBSYSTEM_H
#define LIBSYSTEMS_AXISALIGNEDBBSYSTEM_H
#include <LibComponents/Model.h>
#include <LibCommon/System.h>
#include <LibCommon/Entity.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
namespace Systems {
	class AxisAlignedBBSystem : public LibCommon::System {
	public:
		AxisAlignedBBSystem();
		virtual void Init() override;
		virtual void OnEntityUpdate(LibCommon::Entity* e, Components::IComponent* c) override;
	private:
		Eigen::AlignedBox3f calculateBox(const Components::Model& mod);

	};
}
#endif