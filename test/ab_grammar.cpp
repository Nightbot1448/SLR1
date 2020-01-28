#include "gtest/gtest.h"
#include "SLR_parser.h"

class OtherParserTest : public ::testing::Test {
protected:
    //Lang : a^*ba^*b
    OtherParserTest() {
        Grammar grammar;
        grammar.emplace('S', "AA");
        grammar.emplace('A', "aA");
        grammar.emplace('A', "b");
        parser = SLR1_parser(grammar);
    }

    SLR1_parser parser;
};

TEST_F(OtherParserTest, OnlyB) {
    std::string in("bb");
    // std::cout << "\tInput: " << in << std::endl;
    EXPECT_EQ(parser.parse(in), true);
}

TEST_F(OtherParserTest, SameHalf) {
    std::string in("abab");
    // std::cout << "\tInput: " << in << std::endl;
    EXPECT_EQ(parser.parse(in), true);
}

TEST_F(OtherParserTest, DiffHalf) {
    std::string in("aabaaab");
    // std::cout << "\tInput: " << in << std::endl;
    EXPECT_EQ(parser.parse(in), true);
}

TEST_F(OtherParserTest, FailureOnlyA) {
    std::string in("aaa");
    // std::cout << "\tInput: " << in << std::endl;
    EXPECT_EQ(parser.parse(in), false);
}

TEST_F(OtherParserTest, FailureOneB) {
    std::string in("abaa");
    // std::cout << "\tInput: " << in << std::endl;
    EXPECT_EQ(parser.parse(in), false);
    in = "aab";
    EXPECT_EQ(parser.parse(in), false);
}

TEST_F(OtherParserTest, FailureOtherChar) {
    std::string in("ababc");
    // std::cout << "\tInput: " << in << std::endl;
    EXPECT_EQ(parser.parse(in), false);
}