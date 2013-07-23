//! \brief The classes in this file are common markers
//!        that are used to gain more control over who can
//!        handle a message, if you like you could derive from these
//!        bit it really will not get you anything
#include "Get.hpp"
#ifndef LIBCOMMON_MESSAGEMARKERS_H
#define LIBCOMMON_MESSAGEMARKERS_H

namespace LibCommon {
	namespace Tags {
		class CameraTransform3D : public Get<Eigen::Matrix4f> {};
		class Transform3D : public Get<Eigen::Affine3f> {};
		class Velocity3D : public Get<Eigen::Affine3f> {};

		class Transform2D : public Get<Eigen::Affine2f> {};
		class Velocity2D : public Get<Eigen::Affine2f> {};
	}
}

#endif