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
		std::unique_ptr<IComponent> removeComponent(int index);
		void AddComponent(IComponent* c);
		void AddComponent(Entity* e);
		void AddEntity(Entity* e);
	protected:
		Event _messenger;
		virtual void OnConnect() override;
	private:
		void forwardBubble(Bubbly* msg);
		vector<std::unique_ptr<IComponent>> Components;
		
	};
}
#endif
