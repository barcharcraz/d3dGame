#include <gtest/gtest.h>
#include <ecs.h>
using namespace sparse::ecs;
struct TestStruct {
    static ComponentType stype;
    ComponentType compType = TestStruct::stype;
    size_t size = sizeof(TestStruct);
    Entity ent;
    double value;
};
ComponentType TestStruct::stype = GenID();
struct TestStructD : public Component {
    static ComponentType stype;
    TestStructD() {
        size = sizeof(TestStructD);
        type = TestStructD::stype;
    }
    int value;
};
ComponentType TestStructD::stype = GenID();
TEST(RowTests, TestPushPop) {
    Row r;
    TestStruct t;
    t.value = 42;
    r.push_back(t);
    auto& val = *r.begin<TestStruct>();
    ASSERT_EQ(val.value, 42);
    ASSERT_EQ(val.compType, t.compType);
    ASSERT_EQ(val.size, t.size);
    ASSERT_EQ(val.size, sizeof(TestStruct));
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
