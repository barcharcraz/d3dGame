#ifndef UTILS_SETS_H
#define UTILS_SETS_H
#include <set>
namespace utils {
	template<typename T>
	bool subset(const std::set<T>& lhs, const std::set<T>& rhs) {
		for (auto& elm : rhs) {
			if (lhs.count(elm) == 0) {
				return false;
			}
		}
		return true;
	}
}

#endif