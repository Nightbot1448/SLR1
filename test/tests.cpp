#include "gtest/gtest.h"
#include "SLR_parser.h"

class ParserTest : public ::testing::Test {
protected:

    ParserTest() {
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

TEST_F(ParserTest, SuccesNumber) {
    std::string in("n");
    // std::cout << "\tInput: " << in << std::endl;
    EXPECT_EQ(parser.parse(in), true);
}

TEST_F(ParserTest, SuccesNegativeNumber) {
    std::string in("-n");
    // std::cout << "\tInput: " << in << std::endl;
    EXPECT_EQ(parser.parse(in), true);
}

TEST_F(ParserTest, SuccesSumOfPositiveNumbers) {
    std::string in("n+n");
    // std::cout << "\tInput: " << in << std::endl;
    EXPECT_EQ(parser.parse(in), true);
}

TEST_F(ParserTest, SuccesMultiplyWithNegNumberWithFewMinuses) {
    std::string in("n*---n");
    // std::cout << "\tInput: " << in << std::endl;
    EXPECT_EQ(parser.parse(in), true);
}

TEST_F(ParserTest, SuccesAllInOne) {
    std::string in("n-n+(n*n--n/n)+n");
    // std::cout << "\tInput: " << in << std::endl;
    EXPECT_EQ(parser.parse(in), true);
}

TEST_F(ParserTest, FailureTwoOpInSequence) {
    std::string in("n*/n");
    // std::cout << "\tInput: " << in << std::endl;
    EXPECT_EQ(parser.parse(in), false);
}

TEST_F(ParserTest, FailureWithoutCloseBracket) {
    std::string in("n*(n");
    // std::cout << "\tInput: " << in << std::endl;
    EXPECT_EQ(parser.parse(in), false);
}

TEST_F(ParserTest, FailureWithoutOpenBracket) {
    std::string in("n*-n)");
    // std::cout << "\tInput: " << in << std::endl;
    EXPECT_EQ(parser.parse(in), false);
}

TEST_F(ParserTest, FailureTwoNumInSequence) {
    std::string in("n*-nn");
    // std::cout << "\tInput: " << in << std::endl;
    EXPECT_EQ(parser.parse(in), false);
}

int main (int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}