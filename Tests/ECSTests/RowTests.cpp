#include <gtest/gtest.h>
#include <ecs.h>
#include <type_traits>
using namespace sparse::ecs;
struct TestStruct {
    static ComponentInfo sinfo;
    ComponentInfo* info = &sinfo;
    double value;
};
ComponentInfo TestStruct::sinfo = {GenID(), 
sizeof(TestStruct), 
&sparse::ecs::DefCompCopyFunc<TestStruct>, 
&sparse::ecs::DefCompDeinitFunc<TestStruct>};
struct TestStructD : public Component {
    static ComponentInfo sinfo;
    TestStructD() {
        info = &sinfo;
    }
    int value;
};
ComponentInfo TestStructD::sinfo = {
	GenID(), sizeof(TestStructD), 
	&sparse::ecs::DefCompCopyFunc<TestStructD>, 
	&sparse::ecs::DefCompDeinitFunc<TestStructD>};

TEST(RowTests, TestPushPop) {
    Row r;
    TestStruct t;
    t.value = 42;
    r.push_back(t);
    auto& val = *r.begin<TestStruct>();
    ASSERT_EQ(val.value, 42);
    ASSERT_EQ(val.info->type, t.info->type);
    ASSERT_EQ(val.info->size, t.info->size);
    ASSERT_EQ(val.info->size, sizeof(TestStruct));
}
TEST(RowTests, TestIndexing) {
    Row r;
    TestStruct t1;
    TestStruct t2;
    TestStruct t3;
    t1.value = 1;
    t2.value = 2;
    t3.value = 3;
    r.push_back(t1);
    r.push_back(t2);
    r.push_back(t3);
    ASSERT_EQ(r.at<TestStruct>(0).value, 1);
}
TEST(RowTests, TestBack) {
    Row r;
    TestStruct t1;
    TestStruct t2;
    TestStruct t3;
    t1.value = 1;
    t2.value = 2;
    t3.value = 3;
    r.push_back(t1);
    r.push_back(t2);
    r.push_back(t3);
    ASSERT_EQ(((TestStruct*)r.back())->value, 3);
}
struct TrivialTest_struct {
    static ComponentInfo sinfo;
    ComponentInfo* info;
    int val;
};
ComponentInfo TrivialTest_struct::sinfo = {GenID(), 
sizeof(TrivialTest_struct), 
DefCompCopyFunc<TrivialTest_struct>, 
DefCompDeinitFunc<TrivialTest_struct>};
TEST(RowTests, TestTrivialCopy) {
    ASSERT_TRUE(std::is_trivial<TrivialTest_struct>::value);
    TrivialTest_struct tstruct;
    tstruct.info = &TrivialTest_struct::sinfo;
    tstruct.val = 4;
    Row r1;
    Row r2;
    r1.push_back(tstruct);
    r2 = r1;
    ASSERT_EQ(((TrivialTest_struct*)r1.back())->val, 4);
    ASSERT_EQ(((TrivialTest_struct*)r2.back())->val, 4);
}
struct NonTrivialTest_struct {
    static ComponentInfo sinfo;
    ComponentInfo* info;
    std::string value;
};
ComponentInfo NonTrivialTest_struct::sinfo = GenDefCompInfo<NonTrivialTest_struct>();
TEST(RowTests, TestNonTrivialCopy) {
    ASSERT_FALSE(std::is_trivial<NonTrivialTest_struct>::value);
    NonTrivialTest_struct tests;
    tests.value = "Initial Value";
    tests.info = &NonTrivialTest_struct::sinfo;
    Row r1;
    Row r2;
    r1.push_back(tests);
    ASSERT_EQ(((NonTrivialTest_struct*)r1.back())->value, "Initial Value");
    r2 = r1;
    ((NonTrivialTest_struct*)r2.back())->value = "New Value";
    ASSERT_EQ(((NonTrivialTest_struct*)r2.back())->value, "New Value");
    ASSERT_EQ(((NonTrivialTest_struct*)r1.back())->value, "Initial Value");
}
