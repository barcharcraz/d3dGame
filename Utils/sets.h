#ifndef UTILS_SETS_H
#define UTILS_SETS_H
#include <set>
#include <algorithm>
#include <iterator>
namespace utils {
	template<typename T>
	bool includes(const T& lhs, const T& rhs) {
		return std::includes(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
	}
}

#endif