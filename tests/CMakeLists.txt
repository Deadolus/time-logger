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

file(GLOB HEADER_FILES ../src/*.h)
file(GLOB SRC_FILES
  ../src/sqlite.cpp
  ../src/pingScanner.cpp
  ../src/bluetoothScanner.cpp
  )
file(GLOB TEST_SRC_FILES
${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp
)

add_executable(${PROJECT_NAME} ${SRC_FILES} ${TEST_SRC_FILES})

target_link_libraries(${PROJECT_NAME} gtest gtest_main gcov sqlite3 bluetooth fmt)

gtest_discover_tests(${PROJECT_NAME})

set(CPPCHECK_PARAMETERS
        --enable=warning,portability,information,missingInclude
        --std=c++11
        --template=\"[{severity}][{id}] {message} {callstack} \(On {file}:{line}\)\"
        --error-exitcode=1
        --inline-suppr
        --verbose
        --suppressions-list=${CMAKE_CURRENT_SOURCE_DIR}/CppCheckSuppressions.txt
        -I${CMAKE_CURRENT_SOURCE_DIR}/../src
        -j 4
        ${CMAKE_CURRENT_SOURCE_DIR}/../src
)
add_custom_target(
        cppcheck
        COMMAND /usr/bin/cppcheck
        ${CPPCHECK_PARAMETERS}
)
add_test(NAME cppcheck COMMAND
  cppcheck ${CPPCHECK_PARAMETERS})
add_dependencies(${PROJECT_NAME} cppcheck)

file(RELATIVE_PATH RELATIVE_SOURCEDIR ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/src/)
set(CLANG-TIDY_PARAMETERS
  -p ${RELATIVE_SOURCEDIR}
  ${HEADER_FILES}
  ${SRC_FILES}
  )
add_test(NAME clang-tidy COMMAND
  clang-tidy ${CLANG-TIDY_PARAMETERS}
  )

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

#-------------------------------------------

#fmt.dev
include(FetchContent)

FetchContent_Declare(
  fmtlib
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG        master
)

FetchContent_GetProperties(fmtlib)
if(NOT fmtlib_POPULATED)
  FetchContent_Populate(fmtlib)
  add_subdirectory(${fmtlib_SOURCE_DIR} ${fmtlib_BINARY_DIR})
endif()

FetchContent_Declare(
  pstreams
  GIT_REPOSITORY git://git.code.sf.net/p/pstreams/code
  GIT_TAG        master
)

FetchContent_GetProperties(pstreams)
if(NOT pstreams_POPULATED)
  FetchContent_Populate(pstreams)
endif()
include_directories(${pstreams_SOURCE_DIR})
