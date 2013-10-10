#include <gtest/gtest.h>
#include <Utils/preprocess.h>

class PreprocessorTests : public ::testing::Test {
public:
    PreprocessorTests() {
        std::vector<std::string> testF = {
            "#version 130\n",
            "struct test_t {\n",
            "vec3 test\n",
            "};\n"
        };
        file = utils::SourceFile(testF);
   
    }
protected:
    utils::SourceFile file;
};

TEST_F(PreprocessorTests, DefineTest) {
    file.add_define("TEST_DEFINE");
    ASSERT_STREQ("#define TEST_DEFINE", file.cdata()[0]);
}
TEST_F(PreprocessorTests, DefineValTest) {
    file.add_define("TEST_DEFINE", "12");
    ASSERT_STREQ("#define TEST_DEFINE 12", file.cdata()[0]);
}
TEST_F(PreprocessorTests, DefineMulTest) {
    file.add_defines(std::vector<std::string>{"TEST_DEFINE1", "TEST_DEFINE2"});
    ASSERT_STREQ("#define TEST_DEFINE1", file.cdata()[1]);
    ASSERT_STREQ("#define TEST_DEFINE2", file.cdata()[0]);

}

