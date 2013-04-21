#include "stdafx.h"
#include "Transform2D.h"

using namespace LibCommon;
Transform2D::Transform2D() {
	//the default constructor
}
Transform2D::Transform2D(Eigen::Affine2f transform)
	: _mtransform(transform) 
{
	//no body, just init list
}


#pragma region accessors

const Eigen::Affine2f& Transform2D::getTransform() const {
	return _mtransform;
}

void Transform2D::init() {
	receive.connect([&](IMessage* msg) {
		getTransform(dynamic_cast<Get<Eigen::Affine2f>* >(msg));
	});
}

Eigen::Affine2f& Transform2D::getTransform() {
	return _mtransform;
}

void Transform2D::setTransform(Eigen::Affine2f &transform) {
	_mtransform = transform;
}
#pragma endregion

void Transform2D::getTransform(Get<Eigen::Affine2f> &msg) {
	msg.value = &_mtransform;
}
void Transform2D::getTransform(Get<Eigen::Affine2f> *msg) {
	msg->value = &_mtransform;
}