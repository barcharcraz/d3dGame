#ifndef UTILS_FILES_H
#define UTILS_FILES_H

namespace utils {
	template<typename T>
	inline T clamp(T x, T a, T b) {
		if (x > b)
			return b;
		if (x < a)
			return a;
		return x;
	}
	
}

#endif