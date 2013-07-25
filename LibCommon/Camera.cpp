#include "stdafx.h"
#include "Camera.h"
#include "Markers.h"
namespace LibCommon {
	Camera::Camera() {
		init();
	}
	void Camera::init() {
		//this matrix has no FOV
		_cameraMtx << 
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 1, 0;
		
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