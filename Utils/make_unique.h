//! \brief this calss defines a std::make_unique for those
//! standard libraries that do not support it yet, NEVER
//! #include this file directly, instead include config.h in
//! your precompiled header file
#ifndef UTILS_MAKE_UNIQUE_H
#define UTILS_MAKE_UNIQUE_H
#include <memory>
#include <config.h>
#ifndef HAS_MAKE_UNIQUE
namespace std {
    template<typename T, typename... Args>
    unique_ptr<T> make_unique(Args&&... args) {
        return unique_ptr<T>(new T(std::forward<Args>(args)...));
    }
}
#endif
#endif