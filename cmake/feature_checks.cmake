INCLUDE(CheckCXXSourceCompiles)
MACRO(check_make_unique)
    CHECK_CXX_SOURCE_COMPILES(
    "
    #include <memory>
    int main() {
        std::unique_ptr<int> foo = std::make_unique<int>(4);
    }
    " HAS_MAKE_UNIQUE)
ENDMACRO(check_make_unique)
MACRO(check_is_trivially_copyable)
    CHECK_CXX_SOURCE_COMPILES(
    "
    #include <type_traits>
    int main() {
        bool val = std::is_trivially_copyable<int>::value;
    }
    " HAS_IS_TRIVIALLY_COPYABLE)
ENDMACRO(check_is_trivially_copyable)
