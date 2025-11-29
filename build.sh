#!/bin/bash

# 构建脚本，自动识别标准库路径并配置CMake，包含依赖检查

echo "开始构建googletest-template项目..."

# 检查是否在项目根目录
if [ ! -f "CMakeLists.txt" ]; then
    echo "错误: 请在项目根目录运行此脚本"
    exit 1
fi

# 检查并安装依赖
check_and_install_dependencies() {
    echo "检查项目依赖..."
    
    # 检测操作系统类型
    if [[ "$OSTYPE" == "linux-gnu"* ]]; then
        # Linux系统
        echo "检测到Linux系统，检查glog依赖..."
        
        # 检查glog是否已安装
        if dpkg -l | grep -q libgoogle-glog-dev; then
            echo "✓ glog库已安装"
        else
            echo "✗ glog库未安装"
            echo "请安装glog库后再继续构建:"
            echo "  sudo apt-get update"
            echo "  sudo apt-get install -y libgoogle-glog-dev"
            echo ""
            echo "是否现在安装glog依赖？(y/n)"
            read -r install_deps
            
            if [ "$install_deps" = "y" ] || [ "$install_deps" = "Y" ]; then
                echo "正在安装glog依赖..."
                sudo apt-get update
                sudo apt-get install -y libgoogle-glog-dev
                
                if [ $? -ne 0 ]; then
                    echo "错误: glog依赖安装失败，请手动安装后重试"
                    exit 1
                fi
                echo "glog依赖安装成功！"
            else
                echo "警告: 在未安装glog依赖的情况下继续构建可能会失败"
                echo "按Enter键继续，或按Ctrl+C取消..."
                read -r
            fi
        fi
        
        # 检查Google Test是否已安装
        if dpkg -l | grep -q libgtest-dev; then
            echo "✓ Google Test已安装"
        else
            echo "✗ Google Test未安装"
            echo "建议安装Google Test:"
            echo "  sudo apt-get install -y libgtest-dev"
        fi
    elif [[ "$OSTYPE" == "darwin"* ]]; then
        # macOS系统
        echo "检测到macOS系统，检查glog依赖..."
        
        # 检查glog是否已安装
        if brew list | grep -q glog; then
            echo "✓ glog库已安装"
        else
            echo "✗ glog库未安装"
            echo "请安装glog库:"
            echo "  brew install glog"
        fi
        
        # 检查Google Test是否已安装
        if brew list | grep -q googletest; then
            echo "✓ Google Test已安装"
        else
            echo "✗ Google Test未安装"
            echo "建议安装Google Test:"
            echo "  brew install googletest"
        fi
    elif [[ "$OSTYPE" == "msys"* ]]; then
        # Windows系统 (MinGW)
        echo "检测到Windows系统，使用MinGW"
        echo "请确保已安装glog和Google Test依赖"
    else
        echo "警告: 未识别的操作系统类型: $OSTYPE"
        echo "请确保已手动安装所需依赖"
    fi
}

# 执行依赖检查
check_and_install_dependencies

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
