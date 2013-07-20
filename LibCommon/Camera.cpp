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
		receive.connect<Marked<Tags::Camera, Get<Eigen::Affine3f> > >([this](Get<Eigen::Affine3f> * msg) {this->handleGet(msg); });
	}
	void Camera::handleGet(Get<Eigen::Affine3f> * msg) {
		Marked<Tags::Transform, Get<Eigen::Affine3f> > transMsg(this);
		send(&transMsg);
		(*msg->value) = (*transMsg.value) * _cameraMtx;
	}
}