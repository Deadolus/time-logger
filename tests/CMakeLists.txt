cmake_minimum_required(VERSION 3.10)
project(time-logger-test)
include(GoogleTest)
find_package(GTest REQUIRED)
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

target_link_libraries(${PROJECT_NAME} GTest::Main GTest::GTest gcov sqlite3)

gtest_discover_tests(${PROJECT_NAME})


#-------------------------------------------

#GTest stuff
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()
