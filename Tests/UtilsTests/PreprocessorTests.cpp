#include <gtest/gtest.h>
#include <Utils/preprocess.h>

class PreprocessorTests : public ::testing::Test {
public:
protected:
    
}

TEST(PreprocessorTests, DefineTest) {
    std::vector<std::string> testF = {
        "#version 130\n",
        "struct test_t {\n",
        "vec3 test\n",
        "};\n"
        };
    utils::SourceFile test(testF);
    test.add_define("TEST_DEFINE");
    ASSERT_STREQ("#define TEST_DEFINE", test.cdata()[0]);

}
TEST(PreprocessorTests, DefineValTest) {
    std::vector<std::string> testF
}

