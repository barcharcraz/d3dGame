//! \brief The classes in this file are common markers
//!        that are used to gain more control over who can
//!        handle a message, if you like you could derive from these
//!        but it really will not get you anything
#include "Get.hpp"
#ifndef LIBCOMMON_MESSAGEMARKERS_H
#define LIBCOMMON_MESSAGEMARKERS_H

namespace LibCommon {
	namespace Tags {
		template<typename T, typename U>
		class Tagged : public T, public U {
		public:
			template<typename... Args>
			Tagged(Args... params) : T(), U(params...) {}
		};
		namespace Internal {
			class CameraTransform{};
			class Transform{};
			class Velocity{};
		}
		typedef Tagged<Internal::Transform, Get<Eigen::Affine3f> > Transform3D;
		typedef Tagged<Internal::Velocity, Get<Eigen::Affine3f> > Velocity3D;
		typedef Tagged<Internal::Transform, Get<Eigen::Affine2f> > Transform2D;
		typedef Tagged<Internal::Velocity, Get<Eigen::Affine2f> > Velocity2D;
		typedef Tagged<Internal::CameraTransform, Get<Eigen::Matrix4f> > CameraTransform3D;

		
	}
}

#endif