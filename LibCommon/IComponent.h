#pragma once
#include <atomic>
namespace LibCommon {
	class IComponent {
	public:
		virtual void Update() = 0;
		
	};
}