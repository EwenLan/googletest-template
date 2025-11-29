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
- **Glog**: Google日志库（必需）
- **C++编译器**: 支持C++17的编译器（GCC 7+, Clang 5+, MSVC 2019+）
- **Google Test**: 自动通过CMake FetchContent下载，无需手动安装

## 构建步骤

### 1. 安装依赖项

#### 在Ubuntu/Debian系统上
```bash
# 更新包管理器
sudo apt-get update

# 安装基本构建工具
sudo apt-get install -y build-essential cmake

# 安装glog日志库
sudo apt-get install -y libgoogle-glog-dev
```

#### 在CentOS/RHEL系统上
```bash
# 安装EPEL仓库（提供glog包）
sudo yum install -y epel-release

# 安装构建工具和依赖
sudo yum install -y gcc-c++ cmake glog-devel
```

#### 在macOS系统上（使用Homebrew）
```bash
# 安装依赖
brew install cmake glog
```

#### 从源码构建glog（所有平台通用）
如果通过包管理器安装遇到问题，或者需要特定版本的glog，可以从源码构建：
```bash
# 克隆glog仓库
git clone https://github.com/google/glog.git
cd glog

# 配置并构建
mkdir build && cd build
cmake .. -DBUILD_SHARED_LIBS=ON -DCMAKE_INSTALL_PREFIX=/usr/local
make -j$(nproc)
sudo make install

# 更新库缓存
if [ -f /etc/ld.so.conf.d ]; then
    sudo ldconfig
fi
cd ../..
rm -rf glog  # 可选：清理临时文件
```

### 2. 使用自动构建脚本

项目提供了自动化构建脚本，可以自动检查依赖并构建项目：

```bash
# 确保脚本有执行权限
chmod +x build.sh

# 运行构建脚本
./build.sh
```

### 3. 手动构建步骤

如果需要自定义构建选项，可以使用手动构建步骤：

```bash
# 进入构建目录
mkdir -p build && cd build

# 基本配置
cmake ..

# 如果glog安装在非标准路径，可以指定其位置
# cmake .. -Dglog_DIR=/path/to/glog/share/cmake/glog
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

# 指定glog的安装路径（如果安装在非标准位置）
cmake -Dglog_DIR=/path/to/glog/share/cmake/glog ..
```

## Linux系统下的常见问题

### 找不到glog库

如果CMake报错找不到glog库，请尝试以下解决方案：

1. 确认glog已正确安装
   ```bash
   dpkg -l | grep libgoogle-glog-dev  # Ubuntu/Debian
   rpm -qa | grep glog               # CentOS/RHEL
   ```

2. 从源码重新构建glog，确保安装到系统路径

3. 使用-Dglog_DIR选项指定glog的安装位置

4. 检查系统架构是否匹配（32位/64位）

### 链接错误

如果遇到glog相关的链接错误，可能是因为：

1. glog库版本不兼容（建议使用0.6.0或更高版本）
2. 混合使用静态库和动态库
3. 库搜索路径未正确配置

尝试从源码构建glog并使用-DBUILD_SHARED_LIBS=ON选项启用动态库构建。

## 许可证

[MIT License](LICENSE)
