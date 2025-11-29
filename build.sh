#!/bin/bash

# 构建脚本，自动识别标准库路径并配置CMake

echo "开始构建googletest-template项目..."

# 检查是否在项目根目录
if [ ! -f "CMakeLists.txt" ]; then
    echo "错误: 请在项目根目录运行此脚本"
    exit 1
fi

# 创建或清理build目录
if [ -d "build" ]; then
    echo "清理现有build目录..."
    rm -rf build/*
else
    echo "创建build目录..."
    mkdir -p build
fi

# 自动识别标准库路径（macOS系统）
echo "自动识别标准库路径..."
if command -v xcrun &> /dev/null; then
    SDK_PATH=$(xcrun --show-sdk-path)
    if [ -d "$SDK_PATH/usr/include/c++/v1" ]; then
        STDLIB_PATH="$SDK_PATH/usr/include/c++/v1"
        echo "找到macOS标准库路径: $STDLIB_PATH"
    else
        echo "警告: 未找到标准C++库路径，将使用系统默认路径"
        STDLIB_PATH=""
    fi
else
    echo "警告: 未找到xcrun命令，将使用系统默认路径"
    STDLIB_PATH=""
fi

# 进入build目录并配置CMake
echo "配置CMake..."
cd build

# 配置CMake，确保标准库路径正确设置
if [ -n "$STDLIB_PATH" ]; then
    cmake .. -DSTDLIB_INCLUDE_PATH="$STDLIB_PATH" -DCMAKE_CXX_FLAGS="-I$STDLIB_PATH"
else
    cmake ..
fi

if [ $? -ne 0 ]; then
    echo "错误: CMake配置失败"
    exit 1
fi

# 构建项目
echo "构建项目..."
make

if [ $? -ne 0 ]; then
    echo "错误: 项目构建失败"
    exit 1
fi

echo "项目构建成功！"
echo "可执行文件位置: $(pwd)/googletest-template"
echo "测试可执行文件位置: $(pwd)/tests/googletest-template_tests"

# 可选：运行测试
echo ""
echo "是否运行测试？(y/n)"
read -r run_tests

if [ "$run_tests" = "y" ] || [ "$run_tests" = "Y" ]; then
    echo "运行测试..."
    ./tests/googletest-template_tests
fi

echo ""
echo "构建脚本执行完成！"
