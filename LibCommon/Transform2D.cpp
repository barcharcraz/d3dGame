#include "stdafx.h"
#include "Transform2D.h"
#include "Marked.h"
#include "MessageMarkers.h"

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
Transform2D::Transform2D(float x, float y) {
	_mtransform = std::unique_ptr<Eigen::Affine2f>(new Eigen::Affine2f(Eigen::Affine2f::Identity()));
	_mtransform->translate(Eigen::Vector2f(x,y));
	init();
}

#pragma region accessors

const Eigen::Affine2f& Transform2D::getTransform() const {
	return *_mtransform;
}

void Transform2D::init() {
	receive.connect<Marked<Tags::Transform, Get<Eigen::Affine2f> >* >([this](Get<Eigen::Affine2f> * msg){this->getTransform(msg);});
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