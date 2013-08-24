#ifndef LIBCOMPONENTS_MESSAGES_H
#define LIBCOMPONENTS_MESSAGES_H
#include "IComponent.h"
#include <memory>
#include <vector>
namespace Components {
	class Messages : public IComponent {
	public:
		void AddMessage(std::unique_ptr<Components::IComponent> && msg);
		void ClearMessages();
	private:
		std::vector<Components::IComponent*> messages;
	};
}


#endif