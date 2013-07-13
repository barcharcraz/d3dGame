#include "stdafx.h"
#include "Camera.h"
#include "Marked.hpp"
namespace LibCommon {
	Camera::Camera() {
		init();
	}
	void Camera::init() {
		receive.connect<Marked<Tags::Camera, Get<Eigen::Vector3f> >* >([this](Get<Eigen::Vector3f> * msg) {this->handleGet(msg); });
	}
	void Camera::handleGet(Get<Eigen::Vector3f> * msg) {
		Marked<Tags::Transform, Get<Eigen::Vector3f> > transMsg(this);
		send(&transMsg);
		msg->value = transMsg.value; //just forward our transform
	}
}