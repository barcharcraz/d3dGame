#ifndef LIBSYSTEMS_AXISALIGNEDBBSYSTEM_H
#define LIBSYSTEMS_AXISALIGNEDBBSYSTEM_H
#include <LibComponents/Model.h>
#include <ecs.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
namespace Systems {
	class AxisAlignedBBSystem : public sparse::ecs::System {
	public:
		AxisAlignedBBSystem();
		static void AABBUpdate(sparse::ecs::Row*, 
			const sparse::ecs::Scene* scene, 
			sparse::ecs::Row* row);
	private:
		static Eigen::AlignedBox3f calculateBox(const Components::Model& mod);

	};
	
}
#endif