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
		Transform2D(Eigen::Affine2f* transform);
		Transform2D(float x, float y);
		const Eigen::Affine2f& getTransform() const;
		Eigen::Affine2f& getTransform();
		void setTransform(Eigen::Affine2f &transform);

	private:
		void getTransform(Get<Transform2D, Eigen::Affine2f> &msg);
		void getTransform(Get<Transform2D, Eigen::Affine2f> *msg);
		std::unique_ptr<Eigen::Affine2f> _mtransform;
		void init();
	};
}

#endif
