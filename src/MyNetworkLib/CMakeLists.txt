cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)




#包含目录下.cc文件
aux_source_directory(./base SRC_BASE)
aux_source_directory(./http SRC_HTTP)
aux_source_directory(./logger SRC_LOGGER)
aux_source_directory(./network SRC_NETWORK)
aux_source_directory(./storage SRC_STORAGE)
aux_source_directory(./timer SRC_TIMER)

add_library(MyNetworkLib SHARED
            ${SRC_BASE}
            ${SRC_HTTP}
            ${SRC_LOGGER}
            ${SRC_NETWORK}
            ${SRC_STORAGE}
            ${SRC_TIMER}
            )

target_link_libraries(MyNetworkLib pthread)

