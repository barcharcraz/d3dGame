#ifndef LIBCOMMON_ENTITY_H
#define LIBCOMMON_ENTITY_H
#include "IComponent.h"
#include <list>
#include <functional>
#include <boost/signals2.hpp>
#include "Messages.h"

namespace LibCommon {
	using namespace std;
	class Entity : public IComponent {
	public:
		Entity();
		virtual void removeComponent(IComponent* c);
		virtual void addComponent(IComponent* c);
		///-------------------------------------------------------------------------------------------------
		/// <summary>	Handles a message, called both when a component sends messages
		/// 			up as well as when messages are sent from outside </summary>
		///
		/// <remarks>	Charlie, 4/8/2013. </remarks>
		///
		/// <param name="message">	The message to handle. </param>
		///-------------------------------------------------------------------------------------------------
		virtual void handleMessage(const IMessage& message);
		///-------------------------------------------------------------------------------------------------
		/// <summary>	Handles a message, called both when a component sends messages
		/// 			up as well as when messages are sent from outside 
		/// 			
		/// 			This version just calls the reference version</summary>
		///
		/// <remarks>	Charlie, 4/8/2013. </remarks>
		///
		/// <param name="message">	The message to handle. </param>
		///-------------------------------------------------------------------------------------------------
		virtual void handleMessage(const IMessage * const message);

	private:
		std::function<void(const IMessage&)> m_handler;
		boost::signals2::connection _mConnection;
		list<IComponent*> Components;

	};
}
#endif