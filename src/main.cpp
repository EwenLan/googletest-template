#include <calculator.h>
#include <glog/logging.h>
#include <log_config.h>

int main(int argc, char *argv[]) {
  // 使用RAII模式初始化日志系统
  // 当main函数结束时，logConfig对象会自动析构，关闭日志系统
  LogConfig logConfig(argv[0]);

  LOG(INFO) << "Starting calculator application";

  Calculator calc;

  // 测试基本运算
  double a = 10.0;
  double b = 5.0;

  LOG(INFO) << "Calculator Demo:";
  LOG(INFO) << a << " + " << b << " = " << calc.add(a, b);
  LOG(INFO) << a << " - " << b << " = " << calc.subtract(a, b);
  LOG(INFO) << a << " * " << b << " = " << calc.multiply(a, b);
  LOG(INFO) << a << " / " << b << " = " << calc.divide(a, b);

  // 测试错误情况
  LOG(INFO) << "Trying division by zero...";
  double result = calc.divide(a, 0.0);
  LOG(INFO) << "Result: " << result
            << " (in a real application, this should return an error)";

  LOG(INFO) << "Calculator application finished";

  // 日志测试
  LOG(INFO) << "This is a line of log in info level";
  LOG(WARNING) << "This is a line of log in warning level";
  LOG(ERROR) << "This is a line of log in error level";
  // 注释掉FATAL级别日志，因为它会导致程序崩溃
  // LOG(FATAL) << "This is a line of log in fatal level";

  // 不需要显式关闭日志系统，RAII模式会在logConfig对象析构时自动关闭

  return 0;
}
