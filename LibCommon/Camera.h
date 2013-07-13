#include "stdafx.h"
#include "IComponent.h"
#include "Markers.h"
namespace LibCommon {
	class Camera : IComponent {
	public:
		Camera();
		Camera(const Eigen::Vector3f& transform);
		Camera(float x, float y, float z);
		Eigen::Vector3f getPosition() const;
		void setPositioon(const Eigen::Vector3f& position);
	private:
		Eigen::Vector3f position;
	};
}