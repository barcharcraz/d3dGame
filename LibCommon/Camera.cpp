#include "stdafx.h"
#include <cmath>
#include <Eigen/Geometry>
#include "Camera.h"
#include "Markers.h"
namespace LibCommon {
	Camera::Camera() {
		init(1,100, 90);
	}
	Camera::Camera(float near, float far) {
		init(near, far, 90);
	}
	Camera::Camera(float near, float far, float fov) {
		init(near, far, fov);
	}
	Camera::Camera(float fov) {
		init(1, 100, fov);
	}
	void Camera::init(float near, float far, float fov) {
		//m33 is the third column and third row
		float m33 = (far / (far - near));
		float m34 = ((far * near) / (far - near));

		//calculate the scale from the fov
		float scale = (1 / (float)tan(fov * 0.5 * (M_PI / 180)));
			
		_cameraMtx << 
			scale, 0,    0,   0,
			0,    scale, 0,   0,
			0,    0,    -m33, -m34,
			0,    0,    -1,   0;
		
	}
	void Camera::OnConnect() {
		messenger->connect(&Camera::handleGet, this);
	}
	void Camera::handleGet(Tags::CameraTransform3D * msg) {
		auto transform = messenger->Get<Tags::Transform3D>();
		_cameraTransform = (*transform).matrix() * _cameraMtx;
		msg->value = &_cameraTransform;
	}
}