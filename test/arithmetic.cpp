#include "gtest/gtest.h"
#include "SLR_parser.h"

class ArithmeticParserTest : public ::testing::Test {
protected:

    ArithmeticParserTest() {
        Grammar grammar;
        grammar.emplace('S', "E");
        grammar.emplace('E', "T");
        grammar.emplace('E', "E+T");
        grammar.emplace('E', "E-T");
        grammar.emplace('T', "F");
        grammar.emplace('T', "T*F");
        grammar.emplace('T', "T/F");
        grammar.emplace('F', "(E)");
        grammar.emplace('F', "-F");
        grammar.emplace('F', "n");
        parser = SLR1_parser(grammar);
    }

    SLR1_parser parser;
};

TEST_F(ArithmeticParserTest, SuccesNumber) {
    std::string in("n");
    // std::cout << "\tInput: " << in << std::endl;
    EXPECT_EQ(parser.parse(in), true);
}

TEST_F(ArithmeticParserTest, SuccesNegativeNumber) {
    std::string in("-n");
    // std::cout << "\tInput: " << in << std::endl;
    EXPECT_EQ(parser.parse(in), true);
}

TEST_F(ArithmeticParserTest, SuccesSumOfPositiveNumbers) {
    std::string in("n+n");
    // std::cout << "\tInput: " << in << std::endl;
    EXPECT_EQ(parser.parse(in), true);
}

TEST_F(ArithmeticParserTest, SuccesMultiplyWithNegNumberWithFewMinuses) {
    std::string in("n*---n");
    // std::cout << "\tInput: " << in << std::endl;
    EXPECT_EQ(parser.parse(in), true);
}

TEST_F(ArithmeticParserTest, SuccesAllInOne) {
    std::string in("n-n+(n*n--n/n)+n");
    // std::cout << "\tInput: " << in << std::endl;
    EXPECT_EQ(parser.parse(in), true);
}

TEST_F(ArithmeticParserTest, FailureTwoOpInSequence) {
    std::string in("n*/n");
    // std::cout << "\tInput: " << in << std::endl;
    EXPECT_EQ(parser.parse(in), false);
}

TEST_F(ArithmeticParserTest, FailureWithoutCloseBracket) {
    std::string in("n*(n");
    // std::cout << "\tInput: " << in << std::endl;
    EXPECT_EQ(parser.parse(in), false);
}

TEST_F(ArithmeticParserTest, FailureWithoutOpenBracket) {
    std::string in("n*-n)");
    // std::cout << "\tInput: " << in << std::endl;
    EXPECT_EQ(parser.parse(in), false);
}

TEST_F(ArithmeticParserTest, FailureTwoNumInSequence) {
    std::string in("n*-nn");
    // std::cout << "\tInput: " << in << std::endl;
    EXPECT_EQ(parser.parse(in), false);
}