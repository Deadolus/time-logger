cmake_minimum_required(VERSION 3.10)
project(time-logger)
file(GLOB SRC_FILES *.cpp)
add_executable (${PROJECT_NAME} ${SRC_FILES} )
target_link_libraries(${PROJECT_NAME} sqlite3 bluetooth fmt)
add_custom_target(run COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME})

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
  include_directories(${pstreams_SOURCE_DIR})
endif()
