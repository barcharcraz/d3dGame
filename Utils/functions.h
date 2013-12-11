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
        Defer(const Defer& other) = delete;
        Defer& operator=(const Defer& other) = delete;
        Defer(Defer&& other) = default;
        Defer& operator=(Defer&& other) = default;
        ~Defer() {
            func();
        }
    private:
        T func;
    };
    template<typename T>
    Defer<T> make_defer(const T& arg) {
        return Defer<T>(arg);
    }
}

#endif