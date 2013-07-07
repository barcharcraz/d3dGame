#include <gtest/gtest.h>
#include <LibCommon/ObjFile.h>

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <istream>
#include <vector>
#include <string>
using namespace Eigen;
using namespace std;
class ObjFixture : public testing::Test {
public:
	ObjFixture()
		: shortVert(std::stringstream("v 1.0 2.0 3.0 4.0")),
		longVert(std::stringstream("v 1.0 2.0 3.0 4.0 \nv 5.0 6.0 7.0 8.0")),
		short3Vert(std::stringstream("v 1.0 2.0 3.0")),
		long3Vert(std::stringstream("v 1.0 2.0 3.0 \nv 4.0 5.0 6.0")),
		shortIndex(std::stringstream("f 0 1 2")),
		longIndex(std::stringstream("f 0 1 2 3 4")),
		lineIndex(std::stringstream("f 0 1 2 \n f 2 1 0"))
	{
	}
	LibCommon::ObjFile long3Vert;
	LibCommon::ObjFile shortVert;
	LibCommon::ObjFile longVert;
	LibCommon::ObjFile short3Vert;
	LibCommon::ObjFile shortIndex;
	LibCommon::ObjFile longIndex;
	LibCommon::ObjFile lineIndex;
	
};
TEST_F(ObjFixture, LongVertContent) {
	auto result = longVert.verts();
	ASSERT_EQ(result[0], Eigen::Vector4f(1.0f, 2.0f, 3.0f, 4.0f));
}
TEST_F(ObjFixture, LongVertContent2) {
	auto result = longVert.verts();
	ASSERT_EQ(result[1], Eigen::Vector4f(5.0f, 6.0f, 7.0f, 8.0f));
}
TEST_F(ObjFixture, short3Vert) {
	auto result = short3Vert.verts();
	ASSERT_EQ(result[0], Eigen::Vector4f(1.0f, 2.0f, 3.0f, 1.0f));
}
TEST_F(ObjFixture, long3Vert) {
	auto result = long3Vert.verts();
	vector<Vector4f> expected{ Vector4f(1.0f, 2.0f, 3.0f, 1.0f), Vector4f(4.0f, 5.0f, 6.0f, 1.0f) };
	ASSERT_EQ(result, expected);
}
TEST_F(ObjFixture, noIndexTest1) {
	auto result = shortVert.indices();
	ASSERT_EQ(result, std::vector<int>());
}
TEST_F(ObjFixture, noIndexTest2) {
	auto result = longVert.indices();
	ASSERT_EQ(result, vector<int>());
}
TEST_F(ObjFixture, noIndexTest3) {
	auto result = short3Vert.indices();
	ASSERT_EQ(result, vector<int>());
}
TEST_F(ObjFixture, shortIndexTest) {
	auto result = shortIndex.indices();
	vector<int> expected{ 0, 1, 2 };
	ASSERT_EQ(result, expected);
}
TEST_F(ObjFixture, longIndexTest) {
	auto result = longIndex.indices();
	vector<int> expected{ 0, 1, 2, 3, 4 };
	ASSERT_EQ(result, expected);
}
TEST_F(ObjFixture, multilineIndexTest) {
	auto result = lineIndex.indices();
	vector<int> expected { 0, 1, 2, 2, 1, 0 };
	ASSERT_EQ(result, expected);
}
TEST(ObjFileTests, VertReturnLengthTest) {
	std::string vertLine("v 1.0 2.0 3.0 4.0");
	std::stringstream vertStream(vertLine);
	LibCommon::ObjFile testObj(vertStream); //implicit conversion
	auto result = testObj.verts();
	ASSERT_EQ(result.size(), 1);
}
TEST(ObjFileTests, VertContentLength) {
	std::string vertLine("v 1.0 2.0 3.0 4.0");
	std::stringstream vertStream(vertLine);
	LibCommon::ObjFile testObj(vertStream);
	auto result = testObj.verts();
	ASSERT_EQ(result[0], Eigen::Vector4f(1.0f, 2.0f, 3.0f, 4.0f));
}
TEST(ObjFileTests, LongerLengthTest) {
	std::string vertline("v 1.0 2.0 3.0 4.0 \nv 5.0 6.0 7.0 8.0");
	std::stringstream vertStream(vertline);
	LibCommon::ObjFile testObj(vertStream);
	auto result = testObj.verts();
	ASSERT_EQ(result.size(), 2);
}

