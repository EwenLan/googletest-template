# GoogleTest Template Project

这是一个使用CMake构建的C++项目模板，集成了Google Test和Glog库。

## 项目结构

```
.
├── include/           # 头文件目录
│   └── calculator.h   # 示例计算器类头文件
├── src/               # 源代码目录
│   ├── calculator.cpp # 计算器类实现
│   └── main.cpp       # 主程序入口
├── tests/             # 测试目录
│   ├── CMakeLists.txt # 测试目录的CMake配置
│   └── calculator_test.cpp # 计算器类测试
├── build/             # 构建目录
├── CMakeLists.txt     # 主CMake配置文件
├── LICENSE            # 许可证文件
└── README.md          # 项目说明文件
```

## 功能特点

- 使用CMake构建系统
- 支持C++17标准
- 集成Google Test框架进行单元测试
- 集成Glog库进行日志记录
- 提供了计算器类作为示例
- 包含完整的构建和测试配置

## 依赖项

- **CMake 3.14+**: 构建系统
- **Glog**: Google日志库
- **C++编译器**: 支持C++17的编译器（GCC 7+, Clang 5+, MSVC 2019+）
- **Google Test**: 自动通过CMake FetchContent下载，无需手动安装

## 构建步骤

1. 确保已安装所有依赖项

   ```bash
   # 在Ubuntu/Debian上
   sudo apt-get install cmake libgoogle-glog-dev
   
   # 在macOS上（使用Homebrew）
   brew install cmake glog
   ```

2. 进入构建目录

   ```bash
   cd build
   ```

3. 配置项目

   ```bash
   cmake ..
   ```

4. 编译项目

   ```bash
   make
   ```

5. 运行测试

   ```bash
   make test
   # 或者直接运行测试可执行文件
   ./googletest-template_tests
   ```

6. 运行主程序

   ```bash
   ./googletest-template
   ```

## 使用说明

### 计算器类

示例项目提供了一个简单的计算器类，支持以下操作：

- `add(a, b)`: 返回a和b的和
- `subtract(a, b)`: 返回a减b的差
- `multiply(a, b)`: 返回a和b的积
- `divide(a, b)`: 返回a除以b的商，当b为零时抛出异常

### 添加新功能

1. 在`include`目录下添加新的头文件
2. 在`src`目录下添加对应的实现文件
3. 在`tests`目录下添加测试文件
4. 重新构建项目

### 添加新测试

1. 在`tests`目录下创建新的测试文件
2. 确保测试文件名以`_test.cpp`结尾，或者在`tests/CMakeLists.txt`中更新测试文件匹配模式
3. 重新构建和运行测试

## 配置选项

在配置项目时，可以设置以下选项：

```bash
# 设置构建类型（Debug/Release）
cmake -DCMAKE_BUILD_TYPE=Debug ..

# 启用详细日志
cmake -DCMAKE_VERBOSE_MAKEFILE=ON ..
```

## 许可证

[MIT License](LICENSE)
