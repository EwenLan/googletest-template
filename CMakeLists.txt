cmake_minimum_required(VERSION 3.14)
project(googletest-template VERSION 1.0.0 LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 生成compile_commands.json以支持IDE和clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 设置构建类型，默认为Release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# 设置平台特定的编译选项
if(WIN32)
    # Windows平台编译选项
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Zi /Wall /WX")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /Wall")
    # 禁用Windows特定的警告
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
else()
    # Linux/macOS平台编译选项
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Wall -Wextra -pedantic")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -Wall")
    # 添加位置无关代码选项（对于库）
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

# 配置Google Test - 优先使用系统安装的
find_package(GTest QUIET)
if(GTest_FOUND)
    message(STATUS "Found GoogleTest: ${GTest_VERSION}")
    include_directories(${GTEST_INCLUDE_DIRS})
else()
    message(STATUS "GoogleTest not found, please install it manually or ensure it's in your PATH")
    message(STATUS "On Ubuntu: sudo apt-get install libgtest-dev")
    message(STATUS "On macOS: brew install googletest")
endif()

# 查找glog库 - 必需依赖
# 先设置glog查找路径，增加找到的概率
set(glog_DIR "" CACHE PATH "Path to glog installation directory")

# 尝试查找glog
find_package(glog 0.6.0 REQUIRED QUIET)

if(glog_FOUND)
    message(STATUS "Found glog: ${glog_VERSION} (${glog_DIR})")
else()
    # 提供详细的安装指南
    message(FATAL_ERROR "
    glog library not found! Please install it before continuing.
    
    On Ubuntu/Debian:
        sudo apt-get update
        sudo apt-get install -y libgoogle-glog-dev
    
    On CentOS/RHEL:
        sudo yum install -y glog-devel
    
    On macOS:
        brew install glog
    
    If installed in a custom location, set the glog_DIR variable:
        cmake -Dglog_DIR=/path/to/glog/share/cmake/glog ..
    
    Alternatively, you can build glog from source:
        git clone https://github.com/google/glog.git
        cd glog
        mkdir build && cd build
        cmake ..
        make -j4
        sudo make install
    ")
endif()

# 添加源代码
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

# 创建主库
add_library(${PROJECT_NAME}_lib STATIC ${SOURCES})
# 为库目标添加头文件包含路径
target_include_directories(${PROJECT_NAME}_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)
# 链接glog库 - 平台特定的链接配置
if(WIN32)
    # Windows平台下可能需要额外的依赖
    target_link_libraries(${PROJECT_NAME}_lib PUBLIC glog::glog)
    # 添加Windows特定的系统库（如果需要）
    target_link_libraries(${PROJECT_NAME}_lib PRIVATE ws2_32.lib)
else()
    # Linux/macOS平台下的链接配置
    target_link_libraries(${PROJECT_NAME}_lib PUBLIC glog::glog)
endif()

# 如果有main.cpp文件，创建可执行文件
if(EXISTS ${PROJECT_SOURCE_DIR}/src/main.cpp)
    add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/src/main.cpp)
    # 为可执行文件添加头文件包含路径
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib glog::glog)
endif()

# 添加测试子目录
add_subdirectory(tests)

# 安装配置
install(TARGETS ${PROJECT_NAME}_lib
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib)

if(EXISTS ${PROJECT_SOURCE_DIR}/src/main.cpp)
    install(TARGETS ${PROJECT_NAME}
            RUNTIME DESTINATION bin)
endif()

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
        DESTINATION include
        FILES_MATCHING PATTERN "*.h"
        PATTERN "*.hpp")
