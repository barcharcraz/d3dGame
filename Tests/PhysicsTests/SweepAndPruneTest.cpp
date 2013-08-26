#include <gtest/gtest.h>
#include <LibPhysics/SweepAndPrune.h>
#include <array>
#include <Eigen/Core>
#include <Eigen/Geometry>
namespace {
	class SweepAndPruneTest : public ::testing::Test {
	protected:
		SweepAndPruneTest() {
			using namespace Eigen;
			testObjects[0] = AlignedBox3f(Vector3f{ 0, 0, 0 }, Vector3f{ 1, 1, 1 });
			testObjects[1] = AlignedBox3f(Vector3f{ 0.5, 0.5, 0.5 }, Vector3f{ 1, 1, 1, });
			testObjects[2] = AlignedBox3f(Vector3f{ 3, 3, 3 }, Vector3f{ 3, 10, 13 });
			testObjects[3] = AlignedBox3f(Vector3f{ 2, 100, 100 }, Vector3f{ 4, 120, 120 });
			testObjects[4] = AlignedBox3f(Vector3f{ -2, -2, -2 }, Vector3f{ -1, -1, -1 });
		}
		Physics::SweepAndPrune sap;
		//we are going to draw from these in our tests;
		std::array<Eigen::AlignedBox3f, 5> testObjects;
	};

	TEST_F(SweepAndPruneTest, objectAdd) {
		sap.AddObject(testObjects[0], &testObjects[0]);
		ASSERT_EQ(sap.QueryObject(&testObjects[0]).size(), 0);
	}
	TEST_F(SweepAndPruneTest, twoObjectsAddNC) {
		sap.AddObject(testObjects[0], &testObjects[0]);
		sap.AddObject(testObjects[2], &testObjects[2]);
		ASSERT_EQ(sap.QueryObject(&testObjects[0]).size(), 0);
		ASSERT_EQ(sap.QueryObject(&testObjects[2]).size(), 0);
	}
	TEST_F(SweepAndPruneTest, ObjectsAddCollide) {
		sap.AddObject(testObjects[0], &testObjects[0]);
		sap.AddObject(testObjects[1], &testObjects[1]);
		ASSERT_EQ(sap.QueryObject(&testObjects[0]).size(), 1);
		ASSERT_EQ(sap.QueryObject(&testObjects[1]).size(), 1);
	}
	TEST_F(SweepAndPruneTest, ObjectUpdateCollide) {
		using namespace Eigen;
		sap.AddObject(testObjects[0], &testObjects[0]);
		sap.AddObject(testObjects[3], &testObjects[3]);
		ASSERT_EQ(sap.QueryObject(&testObjects[0]).size(), 0);
		ASSERT_EQ(sap.QueryObject(&testObjects[3]).size(), 0);
		sap.UpdateObject(AlignedBox3f{ Vector3f{ 0, 0, 0 }, Vector3f{ 2, 2, 2 } }, &testObjects[3]);
		ASSERT_EQ(sap.QueryObject(&testObjects[0]).size(), 1);
		ASSERT_EQ(sap.QueryObject(&testObjects[3]).size(), 1);
	}
	TEST_F(SweepAndPruneTest, ObjectUpdateUncollide) {
		using namespace Eigen;
		sap.AddObject(testObjects[0], &testObjects[0]);
		sap.AddObject(testObjects[1], &testObjects[1]);
		ASSERT_EQ(sap.QueryObject(&testObjects[0]).size(), 1);
		ASSERT_EQ(sap.QueryObject(&testObjects[1]).size(), 1);
		sap.UpdateObject(AlignedBox3f{Vector3f{3,3,3}, Vector3f{5,5,5}}, &testObjects[1]);
		ASSERT_EQ(sap.NumCollisions(), 0);
		ASSERT_EQ(sap.QueryObject(&testObjects[0]).size(), 0);
		ASSERT_EQ(sap.QueryObject(&testObjects[1]).size(), 0);
	}
	TEST_F(SweepAndPruneTest, AllObjectAddTest) {
		using namespace Eigen;
		for(unsigned int i = 0; i < testObjects.size(); ++i) {
			sap.AddObject(testObjects[i], &testObjects[i]);
		}
		ASSERT_EQ(sap.NumCollisions(), 1);
	}
}
