#ifndef LIBCOMPONENTS_CAMERA_H
#define LIBCOMPONENTS_CAMERA_H

#include "stdafx.h"
#include "IComponent.h"

namespace Components {
	class Camera : public IComponent {
	public:
		Camera();
		Camera(float near, float far);
		Camera(float near, float far, float fov);
		Camera(float fov);
		void init(float near, float far, float fov);
		Eigen::Matrix4f CameraMatrix;
	};
}

#endif