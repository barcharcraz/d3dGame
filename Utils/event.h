#ifndef UTILS_EVENT_H
#define UTILS_EVENT_H
#include <functional>
#include <list>
#include <algorithm>
namespace utils {
	template<typename... Args>
	class Slot {
	public:
		typedef typename std::list<std::function<void(Args...)>>::iterator handle;
		void operator()(Args ... args) {
			for (auto& fun : callbacks) {
				fun(std::forward<Args>(args)...);
			}
		}
		handle connect(const std::function<void(Args...)>& fun) {
			callbacks.push_back(fun);
			return callbacks.end()--;
		}
		template<typename C>
		handle connect(void(C::*fun)(Args...), C* thisptr) {
			return connect([=](Args... args) {
				(thisptr->* fun)(std::forward<Args>(args)...);
			});
		}
		void disconnect(handle fun) {
			auto iter = std::find_if(callbacks.begin(), callbacks.end(), [fun](std::function < T(Args...)>& f) {
				return fun == &f;
			});
			callbacks.erase(iter);
		}
	private:
		std::list<std::function<void(Args...)>> callbacks;
	};
}
#endif