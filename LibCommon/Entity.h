#ifndef LIBCOMMON_ENTITY_H
#define LIBCOMMON_ENTITY_H
#include "IComponent.h"
#include <vector>
#include <list>
#include <memory>
#include <functional>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include "Get.hpp"
#include "IMessage.h"
#include "Bubbly.h"

namespace LibCommon {
	using namespace std;
	class Entity : public IComponent {
	public:
		Entity();
		virtual std::shared_ptr<IComponent> removeComponent(int index);
		virtual void addComponent(IComponent* c);

	private:
		void forwardBubble(Bubbly * msg);
		
		vector<std::shared_ptr<IComponent>> Components;
		Event _messenger;
	};
}
#endif
