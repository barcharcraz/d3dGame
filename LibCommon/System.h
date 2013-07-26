#ifndef LIBCOMMON_SYSTEM_H
#define LIBCOMMON_SYSTEM_H
#include <vector>
#include "IComponent.h"
namespace LibCommon {
	class System : public IComponent {
	public:
		
		virtual ~System() = 0;
	};
	inline System::~System() {};
}
#endif