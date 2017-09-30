cmake_minimum_required(VERSION 3.2)

set(PROJECT_NAME_STR multievilvent-sample)
project(${PROJECT_NAME_STR})

#initial setup
enable_language(C)
enable_language(CXX)
set(CMAKE_CXX_STANDARD 11)
if((${ENABLE_GCOV_SUPPORT}) AND (CMAKE_CXX_COMPILER_ID MATCHES "GNU"))
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
  message("Gcov support is enabled.")
endif()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/3rd-party/global-optimization-test-problems/)

#build sample
add_executable(${PROJECT_NAME_STR} ${PROJECT_SOURCE_DIR}/sample/main.cpp)
