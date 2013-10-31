
remove_definitions(-DUNICODE -D_UNICODE)
set(CMAKE_EXE_LINKER_FLAGS)
find_package(GTest)
include_directories(${GTEST_INCLUDE_DIR})
add_subdirectory(PhysicsTests)
add_subdirectory(UtilsTests)
