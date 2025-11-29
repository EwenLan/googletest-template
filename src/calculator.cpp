#include <calculator.h>

// 加法运算实现
double Calculator::add(double a, double b) {
    return a + b;
}

// 减法运算实现
double Calculator::subtract(double a, double b) {
    return a - b;
}

// 乘法运算实现
double Calculator::multiply(double a, double b) {
    return a * b;
}

// 除法运算实现
double Calculator::divide(double a, double b) {
    // 简单的错误检查，不使用异常
    if (b == 0) {
        return 0; // 实际应用中应该使用错误处理机制
    }
    return a / b;
}
