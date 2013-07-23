#ifndef LIBCOMMON_TRANSFORM_H
#define LIBCOMMON_TRANSFORM_H

#include "stdafx.h"
#include "Get.hpp"
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
			messenger->connect(&Transform::handleGet, this);
		}
		void handleGet(T * msg) {
			msg->value = &transform;
		}
	private:
		typename T::value_type transform;
	};
	template class Transform<Tags::Transform2D>;
	template class Transform<Tags::Transform3D>;
	typedef Transform<Tags::Transform3D> Transform3D;
	typedef Transform<Tags::Transform2D> Transform2D;
}


#endif