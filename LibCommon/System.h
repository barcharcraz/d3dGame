#ifndef LIBCOMMON_SYSTEM_H
#define LIBCOMMON_SYSTEM_H
#include <vector>
#include <tuple>
#include "IComponent.h"
namespace LibCommon {
	class System : public IComponent {
	public:
		std::vector<type_info> in;
		std::vector<type_info> out;
		System(std::vector<type_info> inputs, std::vector<type_info> outputs);
		virtual void Process(Entity* ent);
		virtual ~System() = 0;
	};
	inline System::~System() {};


}
#endif