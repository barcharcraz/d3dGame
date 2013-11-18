#include <gtest/gtest.h>
#include <Utils/preprocess.h>

class PreprocessorTests : public ::testing::Test {
public:
    PreprocessorTests() {
        std::string testF = {
            "#version 130\n"
            "struct test_t {\n"
            "vec3 test\n"
            "};\n"
        };
        testStr = std::move(testF);
    }
protected:
    std::string testStr;
};

TEST_F(PreprocessorTests, DefineTest) {
    utils::add_define(&testStr, "TEST_DEFINE"
    ASSERT_STREQ("#define TEST_DEFINE", &testStr[0]);
}
TEST_F(PreprocessorTests, DefineValTest) {
    utils::add_define(&testStr, "TEST_DEFINE", 12);
    ASSERT_STREQ("#define TEST_DEFINE 12", &testStr[0]);
}
TEST_F(PreprocessorTests, DefineMulTest) {
    utils::add_defines(&testStr, {"TEST_DEFINE1", "TEST_DEFINE2"});
    ASSERT_STREQ("#define TEST_DEFINE1\n#define TEST_DEFINE2", &testStr[0]);

}

