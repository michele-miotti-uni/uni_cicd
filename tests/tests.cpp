#include <gtest/gtest.h>
#include "../src/problems.h"

TEST(Problem1, BalancedNum) {
    EXPECT_EQ(balancedNum(7), "Balanced");
    EXPECT_EQ(balancedNum(959), "Balanced");
    EXPECT_EQ(balancedNum(84593), "Balanced");
    EXPECT_EQ(balancedNum(845693), "Balanced");
    EXPECT_EQ(balancedNum(84592), "Not Balanced");
    EXPECT_EQ(balancedNum(132), "Not Balanced");
}

TEST(Problem2, IsIsogram) {
    EXPECT_TRUE(is_isogram("Dermatoglyphics"));
    EXPECT_FALSE(is_isogram("aba"));
    EXPECT_FALSE(is_isogram("abcdeA"));
    EXPECT_TRUE(is_isogram("_____________abc"));
}

TEST(Problem3, PossiblyPerfect) {
    EXPECT_TRUE(possibly_perfect({'B', 'A', '_', '_'}, {'B', 'A', 'C', 'C'}));
    EXPECT_TRUE(possibly_perfect({'_', '_', '_', '_'}, {'B', 'A', 'C', 'C'}));
    EXPECT_TRUE(possibly_perfect({'D', 'C', 'B', 'A'}, {'B', 'A', 'C', 'C'}));
    EXPECT_FALSE(possibly_perfect({'A', 'B', '_', '_'}, {'A', 'A', 'C', 'C'}));
    EXPECT_FALSE(possibly_perfect({'A', 'B', 'C', '_'}, {'A', 'B', 'D', 'C'}));
    EXPECT_TRUE(possibly_perfect({'A', '_', '_', '_'}, {'B', '_', '_', '_'}));
}

TEST(Problem4, FindOdd) {
    EXPECT_EQ(findOdd({7}), 7);
    EXPECT_EQ(findOdd({0}), 0);
    EXPECT_EQ(findOdd({0, 1, 1, 1, 1}), 0);
    EXPECT_EQ(findOdd({2, 2, 0, 0, 0, 1, 1, 1, 1}), 0);
    EXPECT_EQ(findOdd({2, 2, 0, 0, 0, 0, 1, 1, 1, 1, 1}), 1);
}

TEST(Problem5, EncodeDecode) {
    EXPECT_EQ(encode("hello"), "h2ll4");
    EXPECT_EQ(decode("h3 th2r2"), "hi there");
    EXPECT_EQ(encode("hello world"), "h2ll4 w4rld");
    EXPECT_EQ(decode("h2ll4 w4rld"), "hello world");
}

TEST(Problem6, Bananas) {
    std::unordered_set<std::string> expected = {"b-anana--", "b-anan--a", "b-ana--na", "b-an--ana", "b-a--nana", "b---anana",
                                                "-banana--", "-banan--a", "-bana--na", "-ban--ana", "-ba--nana", "-b--anana"};
    EXPECT_EQ(bananas("bbananana"), expected);

    expected = {"-banana", "b-anana"};
    EXPECT_EQ(bananas("bbanana"), expected);

    expected = {"banana"};
    EXPECT_EQ(bananas("banana"), expected);

    expected = {"ban-an-a", "ban-a-na", "ba-nan-a", "ba-na-na"};
    EXPECT_EQ(bananas("bannanna"), expected);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

