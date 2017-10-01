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

#build optimizer
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${GO_INTERFACE_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rd-party/cmdline)

file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp)

add_library(multi_evolvent_optimizer ${SRC_FILES})
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  target_compile_options(multi_evolvent_optimizer INTERFACE -std=c++11 -Wall -fopenmp -march=native)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  add_definitions(/EHsc /openmp)
endif()

#build sample
add_executable(${PROJECT_NAME_STR} ${PROJECT_SOURCE_DIR}/sample/main.cpp)

target_link_libraries(${PROJECT_NAME_STR} multi_evolvent_optimizer)
target_link_libraries(${PROJECT_NAME_STR} gkls_functions)
target_link_libraries(${PROJECT_NAME_STR} grishagin_functions)
