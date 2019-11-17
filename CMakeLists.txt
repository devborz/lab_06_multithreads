cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_COVERAGE "Build coverage" OFF)

set(
  HUNTER_CACHE_SERVERS
  "https://github.com/bmstu-iu8-cpp-sem-3/hunter-cache"
  CACHE STRING "Default cache server"
)

include("cmake/HunterGate.cmake")

HunterGate(
  URL "https://github.com/cpp-pm/hunter/archive/v0.23.218.tar.gz"
  SHA1 "9a3594a61227967fb92159339ba326701b287b19"
)

add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)
project(calculateSHA)
#string(APPEND CMAKE_CXX_FLAGS " -pedantic -Werror -Wall -Wextra")
#string(APPEND CMAKE_CXX_FLAGS " -Wno-unused-command-line-argument")
#string(APPEND CMAKE_CXX_FLAGS " -Wshadow -Wnon-virtual-dtor")

#hunter_add_package(GTest)
hunter_add_package(Boost COMPONENTS log)
find_package(Boost CONFIG REQUIRED log)
#find_package(GTest CONFIG REQUIRED)


add_library(calculateSHA INTERFACE)
add_library(log INTERFACE)
add_library(picosha2 INTERFACE)

add_executable(calculate
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/main.cpp
)

target_include_directories(calculateSHA INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(log INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(picosha2 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

#target_include_directories(tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
#target_link_libraries(tests GTest::main template)
target_link_libraries(log INTERFACE Boost::log)
target_link_libraries(calculateSHA INTERFACE picosha2 log)
target_link_libraries(calculate calculateSHA)

#enable_testing()
#add_test(NAME unit_tests COMMAND tests)

#if(BUILD_COVERAGE)
#  set(ENABLE_COVERAGE ON CACHE BOOL "Enable coverage build." FORCE)
#  list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
#  find_package(codecov)
#  # TODO: change template word to project name and delete this comment
#  add_coverage(template)
#  add_coverage(tests)
#  list(APPEND LCOV_REMOVE_PATTERNS "'${PROJECT_SOURCE_DIR}/tests/*'")
#  coverage_evaluate()
#endif()
