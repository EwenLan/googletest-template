#include <log_config.h>

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

// 构造函数 - 初始化日志系统
LogConfig::LogConfig(const char* argv0) {
    // 初始化glog，传入程序名作为参数
    google::InitGoogleLogging(argv0);

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
    FLAGS_colorlogtostderr = true;
    // 将日志同时输出到标准输出以便查看
    FLAGS_logtostderr = false;
    FLAGS_alsologtostderr = true;
}

// 析构函数 - 关闭日志系统
LogConfig::~LogConfig() {
    google::ShutdownGoogleLogging();
}

// 移动构造函数实现
LogConfig::LogConfig(LogConfig&&) noexcept {
    // glog不需要特殊的移动处理，因为它主要是全局状态
}

// 移动赋值操作符实现
LogConfig& LogConfig::operator=(LogConfig&&) noexcept {
    // glog不需要特殊的移动处理
    return *this;
}