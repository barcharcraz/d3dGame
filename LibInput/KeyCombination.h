#ifndef LIBINPUT_KEYCOMBINATIONS_H
#define LIBINPUT_KEYCOMBINATIONS_H
#include <array>
#include <initializer_list>
#include "Keys.h"
namespace Input {
	class KeyCombination {
	public:
		KeyCombination(std::initializer_list<Keys> combo);
		//! \brief Constructs a key combination with
		//! only the specified key active
		KeyCombination(Keys);
		KeyCombination();
		void Clear();
		void Clear(Keys key);
		void Set(Keys key);
		bool Get(Keys key);
		//! \brief Match takes a Key combination and 
		//! decides weather this key combination "activates"
		//! the passed in KeyCombination, that is weather all
		//! keys in other are also in this, note that this is NOT
		//! communitive
		bool Match(const KeyCombination& other) const;
	private:
		std::array<bool, Keys::Count> _combo;
	};
}
#endif