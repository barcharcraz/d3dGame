#ifndef H_LIBCOMMON_TRANSFORM2D
#define H_LIBCOMMON_TRANSFORM2D
#include "stdafx.h"
#include "Get.hpp"
#include "IComponent.h"
#include <Eigen/Core>
#include <Eigen/Geometry>

namespace LibCommon {
	class Transform2D : public IComponent {
	public:
		Transform2D();
		Transform2D(Eigen::Affine2f transform);

		const Eigen::Affine2f& getTransform() const;
		Eigen::Affine2f& getTransform();
		void setTransform(Eigen::Affine2f &transform);


	private:
		void getTransform(Get<Eigen::Affine2f> &msg);
		Eigen::Affine2f _mtransform;
		void init();
	};
}

#endif