#ifndef LOG_CONFIG_H
#define LOG_CONFIG_H

#include <glog/logging.h>

// 日志配置类 - 使用RAII模式
class LogConfig {
public:
  // 构造函数 - 初始化日志系统
  LogConfig(const char *argv0);

  // 析构函数 - 关闭日志系统
  ~LogConfig();

  // 禁止拷贝构造和赋值操作
  LogConfig(const LogConfig &) = delete;
  LogConfig &operator=(const LogConfig &) = delete;

  // 允许移动构造和移动赋值（可选）
  LogConfig(LogConfig &&) noexcept;
  LogConfig &operator=(LogConfig &&) noexcept;
};

#endif // LOG_CONFIG_H