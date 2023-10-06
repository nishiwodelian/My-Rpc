# 设置cmake的最低版本和项目名称
cmake_minimum_required(VERSION 3.0)
project(MyRpc)

# 生成debug版本，可以进行gdb调试
set(CMAKE_BUILD_TYPE "Debug")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread -lprotobuf -g")

# 设置项目可执行文件输出的路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
# 设置项目库文件输出的路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)


# 设置项目编译头文件搜索路径 -I
include_directories(${PROJECT_SOURCE_DIR}/src/MyRpc/include)
# 设置MyNetworkLib头文件搜索路径
include_directories(${PROJECT_SOURCE_DIR}/src/MyNetworkLib/base
                    ${PROJECT_SOURCE_DIR}/src/MyNetworkLib/http
                    ${PROJECT_SOURCE_DIR}/src/MyNetworkLib/logger
                    ${PROJECT_SOURCE_DIR}/src/MyNetworkLib/network
                    ${PROJECT_SOURCE_DIR}/src/MyNetworkLib/storage
                    ${PROJECT_SOURCE_DIR}/src/MyNetworkLib/timer
                    )
include_directories(${PROJECT_SOURCE_DIR}/example)
# 设置项目库文件搜索路径 -L
link_directories(${PROJECT_SOURCE_DIR}/lib)

# 设置安装的默认路径
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})
# 将目录安装到 lib/include/ 下（只安装头文件）
install(DIRECTORY ${PROJECT_SOURCE_DIR}/src/ DESTINATION lib/include/
        FILES_MATCHING PATTERN "*.h")

# MyNetworkLib包含了网络库所有的代码
add_subdirectory(src/MyNetworkLib)
# MyRPC包含了网络库所有的代码
add_subdirectory(src/MyRpc)
# example包含了mprpc框架使用的示例代码
add_subdirectory(example)
# test包含测试程序
add_subdirectory(test)