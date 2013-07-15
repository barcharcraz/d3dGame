#ifndef LIBCOMMON_TRANSFORM_H
#define LIBCOMMON_TRANSFORM_H

#include "stdafx.h"
#include "Get.hpp"
#include "Marked.hpp"
#include "Markers.h"
#include "IComponent.h"
#include <Eigen/Core>
#include <Eigen/Geometry>
namespace LibCommon {
	template<typename T>
	class Transform : public IComponent {
	public:
		template<typename... Params>
		Transform(Params... params) : transform(params...) {
			receive.connect<Marked<Tags::Transform, Get<T> > *>([this](Get<T> * msg) {this->handleGet(msg); });
		}
		void handleGet(Get<T> * msg) {
			msg->value = &transform;
		}
	private:
		T transform;
	};
	template class Transform<Eigen::Affine3f>;
	template class Transform<Eigen::Affine3f>;
	typedef Transform<Eigen::Affine3f> Transform3D;
	typedef Transform<Eigen::Affine2f> Transform2D;
}


#endif