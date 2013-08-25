set(utilstests_files
	UtilsTests.cpp
	eventTests.cpp
	)
add_executable(utilsTests ${utilstests_files})
target_link_libraries(utilsTests ${GTEST_LIBRARIES})
add_test(NAME AllUtilsTests COMMAND utilsTests)