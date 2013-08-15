#ifndef UTILS_FUNCTIONS_H
#define UTILS_FUNCTIONS_H
#include <functional>
namespace utils {
	//! \brief The defer function defers the execution of a function
	//! until after the enclosing scope has finished
	template<typename T>
	class Defer {
	public:
		explicit Defer(const T& func_arg)
			: func(func_arg)
		{
			
		}
		~Defer() {
			func();
		}
	private:
		T func;
	};
}

#endif