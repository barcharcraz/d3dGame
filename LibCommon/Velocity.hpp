#ifndef LIBCOMMON_VELOCITY_H
#define LIBCOMMON_VELOCITY_H

#include "stdafx.h"
#include "IComponent.h"
#include "Get.hpp"
#include "UpdateMessage.h"
#include "Marked.hpp"
#include "Markers.h"
namespace LibCommon {
	template<typename T>
	class Velocity : public IComponent {
	public:
		template<typename... Params>
		Velocity(Params... params) : velocity(params...) {
			receive.connect<Marked<Tags::Velocity, Get<T> > * >([this](Get<T> * msg) {this->handleGet(msg); });
			receive.connect<UpdateMessage*>([this](UpdateMessage * msg) {this->handleUpdate(msg); });
		}
		void handleGet(Get<T> * msg) {
			msg->value = &velocity;
		}
		void handleUpdate(UpdateMessage * msg) {
			using namespace std::chrono;
			float ticktime = 1000.0f / static_cast<float>(msg->tick.count());
			auto norm = velocity.matrix() * ticktime;
			Marked<Tags::Transform, Get<T> > transform(this);
			send(&transform);
			(*transform.value) = (*transform.value) * velocity;
		}
	private:
		T velocity;
	};
	template class Velocity<Eigen::Affine2f>;
	template class Velocity<Eigen::Affine3f>;
	typedef Velocity<Eigen::Affine2f> Velocity2D;
	typedef Velocity<Eigen::Affine3f> Velocity3D;
}


#endif