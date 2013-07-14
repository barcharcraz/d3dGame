#include <gtest/gtest.h>
#include <vector>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <iostream>
#ifndef _DEBUG
#pragma comment(lib, "gtest.lib")
#endif
#ifdef _DEBUG
#pragma comment(lib, "gtestd.lib")
#endif
#pragma comment(lib, "LibCommon.lib")
int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	auto rv = RUN_ALL_TESTS();
	std::string in;
	std::cin >> in;
	return rv;
}