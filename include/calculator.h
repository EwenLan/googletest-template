#ifndef CALCULATOR_H
#define CALCULATOR_H

/**
 * 简单计算器类，提供基本的数学运算功能
 */
class Calculator {
public:
    /**
     * 加法运算
     * @param a 第一个操作数
     * @param b 第二个操作数
     * @return 两数之和
     */
    double add(double a, double b);
    
    /**
     * 减法运算
     * @param a 被减数
     * @param b 减数
     * @return 两数之差
     */
    double subtract(double a, double b);
    
    /**
     * 乘法运算
     * @param a 第一个操作数
     * @param b 第二个操作数
     * @return 两数之积
     */
    double multiply(double a, double b);
    
    /**
     * 除法运算
     * @param a 被除数
     * @param b 除数
     * @return 两数之商
     * @throw std::runtime_error 当除数为零时抛出异常
     */
    double divide(double a, double b);
};

#endif // CALCULATOR_H
