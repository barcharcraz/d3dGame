#include <gtest/gtest.h>
#include <ecs.h>
using namespace sparse::ecs;
struct TestStruct {
    ComponentType compType = GenID();
    size_t size = sizeof(TestStruct);
    Entity ent;
    double value;
};
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