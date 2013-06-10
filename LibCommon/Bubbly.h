#ifndef LIBCOMMON_BUBBLY_H
#define LIBCOMMON_BUBBLY_H
#include "IMessage.h"
namespace LibCommon {
	/// <summary> 
	/// The bubbly message wraps another message that is to be sent
	///	outside the contents of the immediate parent of the sender.
	/// Bubbly messages will <em>not</em> be sent to the siblings
	/// of the sender. Note that if you have a huge multi-level 
	/// scene you will need to have one bubbly wrapper per level.
	/// additionally if you use too many bubbly wrappers they end up
	/// getting sent to the immeidate children of the scene
	///
	class Bubbly : IMessage {
	public:
		Bubbly(IMessage * msg);
		//this is the message that we are wrapping
		IMessage * message;
	};
}

#endif