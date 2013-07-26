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
		Camera(float near, float far);
		Camera(float near, float far, float fov);
		Camera(float fov);
		void init(float near, float far, float fov);
		virtual void OnConnect() override;
	private:
		void handleGet(Tags::CameraTransform3D * msg);
		Eigen::Matrix4f _cameraMtx;
		Eigen::Matrix4f _cameraTransform;
	};
}

#endif