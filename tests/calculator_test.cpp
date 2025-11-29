#include <gtest/gtest.h>
#include "calculator.h"

// 测试Calculator类的基本功能
class CalculatorTest : public ::testing::Test {
protected:
    Calculator calc;
    
    // 可以在这里添加测试前的设置
    void SetUp() override {
    }
    
    // 可以在这里添加测试后的清理
    void TearDown() override {
    }
};

// 测试加法功能
TEST_F(CalculatorTest, AddTest) {
    EXPECT_EQ(calc.add(1.0, 2.0), 3.0);
    EXPECT_EQ(calc.add(-1.0, 1.0), 0.0);
    EXPECT_EQ(calc.add(-1.0, -1.0), -2.0);
    EXPECT_NEAR(calc.add(0.1, 0.2), 0.3, 1e-9); // 使用近似相等，因为浮点数精度问题
}

// 测试减法功能
TEST_F(CalculatorTest, SubtractTest) {
    EXPECT_EQ(calc.subtract(5.0, 3.0), 2.0);
    EXPECT_EQ(calc.subtract(-1.0, 1.0), -2.0);
    EXPECT_EQ(calc.subtract(-1.0, -1.0), 0.0);
    EXPECT_NEAR(calc.subtract(0.3, 0.1), 0.2, 1e-9);
}

// 测试乘法功能
TEST_F(CalculatorTest, MultiplyTest) {
    EXPECT_EQ(calc.multiply(2.0, 3.0), 6.0);
    EXPECT_EQ(calc.multiply(-2.0, 3.0), -6.0);
    EXPECT_EQ(calc.multiply(-2.0, -3.0), 6.0);
    EXPECT_EQ(calc.multiply(0.0, 5.0), 0.0);
}

// 测试除法功能
TEST_F(CalculatorTest, DivideTest) {
    EXPECT_EQ(calc.divide(6.0, 3.0), 2.0);
    EXPECT_EQ(calc.divide(-6.0, 3.0), -2.0);
    EXPECT_EQ(calc.divide(-6.0, -3.0), 2.0);
    EXPECT_NEAR(calc.divide(1.0, 3.0), 0.3333333333, 1e-9);
}

// 测试除以零异常
TEST_F(CalculatorTest, DivideByZeroTest) {
    EXPECT_THROW(calc.divide(5.0, 0.0), std::runtime_error);
}

// 测试极端情况
TEST_F(CalculatorTest, ExtremeValuesTest) {
    // 大数测试
    double large = 1e10;
    EXPECT_NEAR(calc.multiply(large, large), 1e20, 1e15);
    
    // 小数测试
    double small = 1e-10;
    EXPECT_NEAR(calc.divide(small, small), 1.0, 1e-9);
}
