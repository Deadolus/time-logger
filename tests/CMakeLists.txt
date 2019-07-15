cmake_minimum_required(VERSION 3.10)
project(time-logger-test)
include(GoogleTest)
enable_testing()
#SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
#SET(CMAKE_CURRENT_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)

if(MSVC)
    #vc 2012 fix for vararg templates
    set(MSVC_COMPILER_DEFS "-D_VARIADIC_MAX=10")
endif()

#SET( CMAKE_CXX_COMPILER /usr/bin/clang++)
#SET( CMAKE_C_COMPILER /usr/bin/clang)
add_definitions(-Wall -Wno-deprecated)
add_definitions(-DGOOGLETEST)
add_definitions(-std=c++1y)
add_definitions(--coverage -g -fprofile-arcs -ftest-coverage)
#SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} --coverage")
SET( CMAKE_EXPORT_COMPILE_COMMANDS ON )
SET(COMMON_INCLUDES
../src
)

SET(TEST_INCLUDES
${CMAKE_CURRENT_SOURCE_DIR}/tests
${CMAKE_CURRENT_SOURCE_DIR}/helpers
)

include_directories(${GTEST_INCLUDE_DIRS} ${COMMON_INCLUDES} ${TEST_INCLUDES})

file(GLOB SRC_FILES ../src/sqlite.cpp)
file(GLOB TEST_SRC_FILES
${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp
)

add_executable(${PROJECT_NAME} ${SRC_FILES} ${TEST_SRC_FILES})

target_link_libraries(${PROJECT_NAME} gtest gtest_main gcov sqlite3)

gtest_discover_tests(${PROJECT_NAME})


#-------------------------------------------

#GTest stuff
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.8.0
)

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()
