# 测试目录的CMakeLists.txt

# 添加可选的标准库路径配置参数
if(NOT STDLIB_INCLUDE_PATH)
    message(STATUS "STDLIB_INCLUDE_PATH not specified, using default system paths")
endif()

# 只有在找到GoogleTest时才创建测试
if(GTest_FOUND)
    # 查找所有测试文件
    file(GLOB TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
    
    # 创建测试可执行文件
    add_executable(${PROJECT_NAME}_tests ${TEST_SOURCES})
    
    # 为测试可执行文件添加头文件包含路径
    target_include_directories(${PROJECT_NAME}_tests
        PRIVATE
            ${PROJECT_SOURCE_DIR}/include
            ${GTEST_INCLUDE_DIRS}
            ${STDLIB_INCLUDE_PATH}
            ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES}
    )
    
    # 确保C++标准设置正确
    set_target_properties(${PROJECT_NAME}_tests PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
    )
    
    # 链接依赖
    target_link_libraries(${PROJECT_NAME}_tests
        PRIVATE
            ${PROJECT_NAME}_lib
            GTest::gtest_main
            glog::glog
    )
    
    # 启用测试发现，自动发现和注册所有测试
    include(GoogleTest)
    gtest_discover_tests(${PROJECT_NAME}_tests)
    
    # 启用测试
    enable_testing()
else()
    message(STATUS "Skipping test creation: GoogleTest not found")
endif()
