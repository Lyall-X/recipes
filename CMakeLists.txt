# documents https://cmake.org/documentation
cmake_minimum_required(VERSION 3.4.1)
project(recipes CXX)

# c++ version required
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# build message output
set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# suffix to debug library version automatically
set(CMAKE_DEBUG_POSTFIX "_d")
set(CMAKE_INSTALL_MESSAGE NEVER)

# set install path
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/bin)

# cmake module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(func)
include(build_net)
include(install_bin)