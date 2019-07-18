cmake_minimum_required(VERSION 3.10)
project(time-logger-main)

set (CMAKE_CXX_STANDARD 17)

#file(GLOB SRC_FILES "*.cpp" "*.h")
#set(COMPONENT_SRCS ${SRC_FILES})

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)
