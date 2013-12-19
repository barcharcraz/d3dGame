#ifndef UTILS_TYPETRAITS_H
#define UTILS_TYPETRAITS_H
#include <config.h>
#include <type_traits>
namespace utils {
    //this is a workaround for standard libraries
    //and compilers like gcc/stdlibc++ that do
    //not have the is_trivially_copyable trait
    //if the workaround activates some things
    //may be un-nessassarly slow but will not
    //break because is_trivial is a superset
    //of is_trivially_copyable
#ifdef HAS_IS_TRIVIALLY_COPYABLE
    template<typename T>
    using is_trivially_copyable = std::is_trivially_copyable<T>;
#else
    template<typename T>
    using is_trivially_copyable = std::is_trivial<T>;
#endif

}

#endif
