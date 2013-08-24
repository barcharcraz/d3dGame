set(physicstest_files
	PhysicsTest.cpp
	SweepAndPruneTest.cpp
	)
add_executable(PhysicsTests ${physicstest_files})
target_link_libraries(PhysicsTests Physics ${GTEST_LIBRARIES})
add_test(NAME AllPhysicsTests COMMAND PhysicsTests)