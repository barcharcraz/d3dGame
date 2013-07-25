#ifndef LIBCOMMON_SCENE_H
#define LIBCOMMON_SCENE_H
#include "IRenderer.h"
#include "Entity.h"
#include "IMessage.h"
#include "IComponent.h"
#include "Bubbly.h"
#include "UpdateMessage.h"
#include "Event.h"
#include <memory>
#include <vector>
#include <chrono>
namespace LibCommon {
	class Scene : public Entity {
	public:
		Scene(IRenderer* pRenderer);
		void Update();
	protected:
		void forwardBubble(Bubbly * msg);
	private:
		
		std::unique_ptr<IRenderer> _pRenderer;
		std::chrono::system_clock _clock;
		std::chrono::system_clock::time_point _lastUpdate;
		std::chrono::milliseconds _rate;
		//Event _messenger;
	};
}
#endif