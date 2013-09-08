
#ifndef UTILS_MAYBE_H
#define UTILS_MAYBE_H

namespace utils {
	template<typename T>
	class Maybe {
	public:
		Maybe()
			: _nothing(true)
		{
			
		}
		Maybe(T val) {
			_val = std::move(val);
			_nothing = true;
		}
		
	private:
		bool _nothing;
		T _val;
	};
}

#endif