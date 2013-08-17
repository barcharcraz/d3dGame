#ifndef LIBSYSTEMS_GROUP_H
#define LIBSYSTEMS_GROUP_H
#include "stdafx.h"
#include <LibCommon/System.h>
#include <string>
#include <vector>
#include <memory>
#include <functional>
namespace Systems {
	enum class Priority {
		LOW,
		MEDIUM,
		HIGH
	};

	class Group : public LibCommon::System {
	public:
		Group(const std::string& name, Priority prio);
		void AddSystem(std::unique_ptr<LibCommon::System> && s);
		template<typename T, typename... Args>
		void AddSystem(Args && ... args) {
			AddSystem(std::make_unique<T>(std::forward<Args>(args)...));
		}
		virtual void Init() override;
		virtual void Process(LibCommon::Entity* ent) override;
		virtual void OnEntityRemove(LibCommon::Entity* ent) override;
	private:
		std::string _name;
		Priority _prio;
		std::vector<std::unique_ptr<LibCommon::System>> _members;
	};

}

#endif