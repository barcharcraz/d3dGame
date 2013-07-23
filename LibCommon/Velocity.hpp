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
			messenger->connect(&Velocity::handleUpdate, this);
			messenger->connect(&Velocity::handleGet, this);
		}
		void handleGet(T * msg) {
			msg->value = &velocity;
		}
		void handleUpdate(UpdateMessage * msg) {
			using namespace std::chrono;
			float ticktime = 1000.0f / static_cast<float>(msg->tick.count());
			auto norm = velocity.matrix() * ticktime;
			auto transform = messenger->Get<T>();
			*transform = *transform * velocity;
		}
	private:
		typename T::value_type velocity;
	};
	template class Velocity<Tags::Velocity3D>;
	template class Velocity<Tags::Velocity2D>;
	typedef Velocity<Tags::Velocity2D> Velocity2D;
	typedef Velocity<Tags::Velocity3D> Velocity3D;
}


#endif