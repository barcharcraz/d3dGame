#pragma once
#include "stdafx.h"
namespace windows {
	//! \brief the ComInitialize class
	//!        inits com when it is constructed
	//!        and removes com when it is destructed
	//!        this means that you can use unique or shared
	//!        to thing that hold COM references
	class ComInitialize {
	public:
		ComInitialize();
		~ComInitialize();
	};
}