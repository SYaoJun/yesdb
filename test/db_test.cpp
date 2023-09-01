#include <iostream>
#include <random>
#include <string>
#include "gtest/gtest.h"

TEST(AddFunctionTest, PositiveNumbers) {
    std::string chinese_question_mark = "？";
    std::string english_question_mark = "?";
    if (chinese_question_mark == english_question_mark) {
        std::cout << "equal" << std::endl;
    } else {
        std::cout << "not equal" << std::endl;
    }
}