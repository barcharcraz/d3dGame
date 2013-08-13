#ifndef UTILS_IDENTIFIER_H
#define UTILS_IDENTIFIER_H

namespace utils {
	static long long int iter = 0;
	template<typename T>
	T GetID() {
		iter += 1;
		return iter;
	}
}

#endif