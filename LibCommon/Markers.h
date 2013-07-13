//! \brief The classes in this file are common markers
//!        that are used to gain more control over who can
//!        handle a message, if you like you could derive from these
//!        bit it really will not get you anything
#ifndef LIBCOMMON_MESSAGEMARKERS_H
#define LIBCOMMON_MESSAGEMARKERS_H

namespace LibCommon {
	namespace Tags {
		class Camera {};
		class Transform {};
		class Velocity {};
	}
}

#endif