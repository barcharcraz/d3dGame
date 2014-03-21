
add_executable(ECSTests RowTests.cpp SceneTests.cpp WorldTests.cpp ECSTests.cpp)
target_link_libraries(ECSTests sparse_ecs ${GTEST_LIBRARIES})
add_test(NAME ECSTests COMMAND ecsRowTests)