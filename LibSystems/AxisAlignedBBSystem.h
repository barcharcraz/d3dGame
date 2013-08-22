#ifndef LIBSYSTEMS_AXISALIGNEDBBSYSTEM_H
#define LIBSYSTEMS_AXISALIGNEDBBSYSTEM_H
#include <LibCommon/System.h>
#include <LibCommon/Entity.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
namespace Systems {
	class AxisAlignedBBSystem : public LibCommon::System {
	public:
		AxisAlignedBBSystem();
		virtual void Process(LibCommon::Entity* ent) override;
	private:
		Eigen::AlignedBox3f calculateBox(const Components::Model& mod);

	};
}
#endif