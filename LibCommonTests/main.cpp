#include <gtest/gtest.h>
#include <vector>
#include <Eigen/Core>
#include <Eigen/Geometry>
#ifndef _DEBUG
#pragma comment(lib, "gtest.lib")
#endif
#ifdef _DEBUG
#pragma comment(lib, "gtestd.lib")
#endif
#pragma comment(lib, "LibCommon.lib")
int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}