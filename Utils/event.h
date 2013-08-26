#ifndef UTILS_EVENT_H
#define UTILS_EVENT_H
#include <functional>
#include <list>
#include <algorithm>
namespace utils {
	template<class>
	class Slot;
	template<typename R, typename... Args>
	class Slot<R(Args...)> {
	public:
		typedef typename std::list<std::function<R(Args...)>>::iterator handle;
		typedef typename std::function<R(Args...)> function_type;
		void operator()(Args ... args) {
			for (auto& fun : callbacks) {
				fun(std::forward<Args>(args)...);
			}
		}
		handle connect(const std::function<R(Args...)>& fun) {
			callbacks.push_back(fun);
			return callbacks.end()--;
		}
		template<typename C>
		handle connect(R(C::*fun)(Args...), C* thisptr) {
			return connect([=](Args... args) {
				(thisptr->* fun)(std::forward<Args>(args)...);
			});
		}
		void disconnect(handle fun) {
			auto iter = std::find_if(callbacks.begin(), callbacks.end(), [fun](std::function < R(Args...)>& f) {
				return fun == &f;
			});
			callbacks.erase(iter);
		}
	private:
		std::list<std::function<R(Args...)>> callbacks;
	};
}
#endif