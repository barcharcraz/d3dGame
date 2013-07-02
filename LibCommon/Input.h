#ifndef LIBCOMMON_INPUT_H
#define LIBCOMMON_INPUT_H
#include "Entity.h"
#include "IComponent.h"
#include "InputMessage.h"
#include <map>
#include "Keys.h"
#include <string>
namespace LibCommon {
	class Input : public Entity {
	public:
		Input(const std::map<int, Keys> &kmap);
		bool HandleKeypress(Keys key);
		bool HandleKeypress(int systemKeyCode);
		bool AddAction(Keys key, std::wstring action);
		bool RemoveAction(std::wstring action);
		bool RemoveAction(Keys key);
	private:
		std::map<Keys, std::wstring> actions;
		const std::map<int, Keys> &keymap;
		Input& operator=(const Input& other); //get rid of default operator=
		/// finds the key bound to a given action if there is
		/// one, if not it returns false
		///
		///\param action the action to search for
		///\param boundKey the return value
		///\return true if it found a key, false otherwise
		bool findAction(std::wstring action, Keys &boundKey);
	};
}
#endif