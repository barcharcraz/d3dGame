#ifndef LIBCOMMON_VELOCITY_H
#define LIBCOMMON_VELOCITY_H

#include "stdafx.h"
#include "IComponent.h"
#include "Get.hpp"
#include "UpdateMessage.h"
#include "Markers.h"
namespace LibCommon {
	template<typename T>
	class Velocity : public IComponent {
	public:
		template<typename... Params>
		Velocity(Params... params) : velocity(params...) {
		}
		void handleGet(Tags::Tagged<Tags::Internal::Velocity, Get<T> > * msg) {
			msg->value = &velocity;
		}
		virtual void OnConnect() override {
			messenger->connect(&Velocity::handleUpdate, this);
			messenger->connect(&Velocity::handleGet, this);
		}
		void handleUpdate(UpdateMessage * msg) {
			using namespace std::chrono;
			float ticktime = 1000.0f / static_cast<float>(msg->tick.count());
			auto norm = velocity.matrix() * ticktime;
			auto transform = messenger->Get<Tags::Tagged<Tags::Internal::Transform, LibCommon::Get<T>>>();
			(*transform) = (*transform) * velocity;
		}
	private:
		typename T velocity;
	};
	template class Velocity<Eigen::Affine2f>;
	template class Velocity<Eigen::Affine3f>;
	typedef Velocity<Eigen::Affine2f> Velocity2D;
	typedef Velocity<Eigen::Affine3f> Velocity3D;
}


#endif