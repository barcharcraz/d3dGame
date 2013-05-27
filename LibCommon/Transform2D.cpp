#include "stdafx.h"
#include "Transform2D.h"

using namespace LibCommon;
Transform2D::Transform2D() {
	//the default constructor
	_mtransform = std::unique_ptr<Eigen::Affine2f>(new Eigen::Affine2f(Eigen::Affine2f::Identity()));
	init();
}
Transform2D::Transform2D(Eigen::Affine2f *transform)
	: _mtransform(transform) 
{
	init();
	//no body, just init list
}


#pragma region accessors

const Eigen::Affine2f& Transform2D::getTransform() const {
	return *_mtransform;
}

void Transform2D::init() {
	BIND(getTransform, Get<Eigen::Affine2f>);
}

Eigen::Affine2f& Transform2D::getTransform() {
	return *_mtransform;
}

void Transform2D::setTransform(Eigen::Affine2f &transform) {
	_mtransform.reset(&transform);
}
#pragma endregion

void Transform2D::getTransform(Get<Eigen::Affine2f> &msg) {
	msg.value = _mtransform.get();
}
void Transform2D::getTransform(Get<Eigen::Affine2f> *msg) {
	msg->value = _mtransform.get();
}