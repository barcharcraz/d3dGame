#include <gtest/gtest.h>
#include <Utils/preprocess.h>
TEST(PreprocessorTests, DefineTest) {
    std::vector<std::string> testF = {
        "#version 130\n",
        "struct test_t {\n",
        "vec3 test\n",
        "};\n"
        };
    utils::add_defines(&testF, {"TEST_DEFINE"});
    ASSERT_STREQ("#define TEST_DEFINE", testF[0].c_str());

}

