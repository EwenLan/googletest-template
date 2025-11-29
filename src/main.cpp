#include <calculator.h>
#include <glog/logging.h>

// 平台特定的头文件和定义
#if defined(_WIN32) || defined(_WIN64)
#include <direct.h>
#define mkdir(path, mode) _mkdir(path)
#define LOG_DIR ".\\logs\\"
#define LOG_DIR_CREATE ".\\logs"
#else
#include <sys/stat.h>
#define LOG_DIR "./logs/"
#define LOG_DIR_CREATE "./logs"
#endif

int main(int argc, char *argv[]) {
  // 初始化glog，传入程序名作为参数
  google::InitGoogleLogging(argv[0]);

  // 在程序退出时自动清理glog资源
  google::InstallFailureSignalHandler();

  // 创建logs目录（如果不存在）
  mkdir(LOG_DIR_CREATE, 0755);

  // 配置glog将日志输出到文件
  // 设置日志文件前缀 - 使用平台兼容的路径
  google::SetLogDestination(google::INFO, LOG_DIR);
  // 设置日志文件最大大小（以MB为单位）
  FLAGS_max_log_size = 10; // 10MB
  // 立即输出日志
  FLAGS_logbuflevel = 0;
  // 将日志同时输出到标准输出以便查看
  FLAGS_logtostderr = false;
  FLAGS_alsologtostderr = true;
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

  return 0;
}
