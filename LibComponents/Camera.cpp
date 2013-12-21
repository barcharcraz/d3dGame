#include "stdafx.h"
#include <cmath>
#include <Eigen/Geometry>
#include "Camera.h"
namespace Components {
    sparse::ecs::ComponentType Camera::stype = sparse::ecs::GenID();
	Camera::Camera() {
		init(1,100, 60);
	}
	Camera::Camera(float near, float far) {
		init(near, far, 60);
	}
	Camera::Camera(float near, float far, float fov) {
		init(near, far, fov);
	}
	Camera::Camera(float fov) {
		init(1, 100, fov);
	}
	void Camera::init(float near, float far, float fov) {
        size = sizeof(Camera);
        type = Camera::stype; 
		//m33 is the third column and third row
		float m33 = ((far + near) / (far - near));
		float m34 = ((far * near) / (far - near));

		//calculate the scale from the fov
		float scale = (1 / (float)tan(fov * 0.5 * (M_PI / 180)));
			
		CameraMatrix << 
			scale, 0,    0,   0,
			0,    scale, 0,   0,
			0,    0,    -m33, -m34,
			0,    0,    -1,   0;

		
	}
}
