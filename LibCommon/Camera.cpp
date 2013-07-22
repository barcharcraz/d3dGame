#include "stdafx.h"
#include "Camera.h"
#include "Marked.hpp"
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
		messenger->connect(&Camera::handleGet, this);
	}
	void Camera::handleGet(Get<Eigen::Matrix4f> * msg) {
		Marked<Tags::Transform, Get<Eigen::Affine3f> > transMsg(this);
		messenger->send(&transMsg);
		msg->value = &_cameraMtx;
	}
}