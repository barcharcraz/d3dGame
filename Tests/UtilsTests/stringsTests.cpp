#include <gtest/gtest.h>
#include <Utils/strings.h>
#include <string>
TEST(TrimTests, SpaceTrim) {
    std::string test = "                     test                   ";
    utils::trim(&test);
    ASSERT_STREQ("test", test.c_str());
}
TEST(TrimTests, DelimTrim) {
    std::string test = "<<<test<<<<";
    utils::trim(&test, '<');
    ASSERT_STREQ("test", test.c_str());
}
TEST(TrimTests, QuoteTrim) {
    std::string test = R"(""""""""""test""""")";
    utils::trim(&test, '"');
    ASSERT_STREQ("test", test.c_str());
}
TEST(TrimTests, EndlineTrim) {
    std::string test = "               test \n";
    utils::trim(&test);
    ASSERT_STREQ("test \n", test.c_str());
}
