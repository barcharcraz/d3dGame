#ifndef LIBCOMPONENTS_CAMERA_H
#define LIBCOMPONENTS_CAMERA_H

#include "stdafx.h"
#include <ecs.h>

namespace Components {
	class Camera : public sparse::ecs::Component {
	public:
        static sparse::ecs::ComponentType stype;
		Camera();
		Camera(float near, float far);
		Camera(float near, float far, float fov);
		Camera(float fov);
		void init(float near, float far, float fov);
		Eigen::Matrix4f CameraMatrix;
	};
}

#endif
