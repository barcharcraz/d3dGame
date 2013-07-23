#ifndef LIBCOMMON_CAMERA_H
#define LIBCOMMON_CAMERA_H

#include "stdafx.h"
#include "IComponent.h"
#include "Markers.h"
#include "Get.hpp"

namespace LibCommon {
	class Camera : public IComponent {
	public:
		Camera();
		void init();
	private:
		void handleGet(Tags::CameraTransform3D * msg);
		Eigen::Matrix4f _cameraMtx;
		Eigen::Matrix4f _cameraTransform;
	};
}

#endif