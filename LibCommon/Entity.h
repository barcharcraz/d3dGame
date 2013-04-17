#ifndef LIBCOMMON_ENTITY_H
#define LIBCOMMON_ENTITY_H
#include "IComponent.h"
#include <vector>
#include <memory>
#include <functional>
#include <boost/signals2.hpp>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include "Get.hpp"
#include "Messages.h"

namespace LibCommon {
	using namespace std;
	class Entity : public IComponent {
	public:
		Entity();
		virtual std::shared_ptr<IComponent> removeComponent(int index);
		virtual void addComponent(IComponent* c);
		///-------------------------------------------------------------------------------------------------
		/// <summary>	Handles a message, called both when a component sends messages
		/// 			up as well as when messages are sent from outside </summary>
		///
		/// <remarks>	Charlie, 4/8/2013. </remarks>
		///
		/// <param name="message">	The message to handle. </param>
		///-------------------------------------------------------------------------------------------------
		virtual void handleMessage(IMessage& message);
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
		virtual void handleMessage(IMessage * message);

	private:
		std::function<void(const IMessage&)> m_handler;
		vector<std::shared_ptr<IComponent> > Components;
	};
}
#endif