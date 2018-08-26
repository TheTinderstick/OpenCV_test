# ----------------------------------------------------------------------------
#  Root CMake file for OpenCV_test
#
#    From the off-tree build directory, invoke:
#      $ cmake <PATH_TO_OPENCV_test_ROOT>
#
# ----------------------------------------------------------------------------

# Disable in-source builds to prevent source tree corruption.
if(" ${CMAKE_SOURCE_DIR}" STREQUAL " ${CMAKE_BINARY_DIR}")
  message(FATAL_ERROR "
FATAL: In-source builds are not allowed.
       You should create a separate directory for build files.
")
endif()

cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
# The version number.
set (OpenCV_test_VERSION_MAJOR 0)
set (OpenCV_test_VERSION_MINOR 1)

project(OpenCV_test CXX)

subdirs(src)

set(CMAKE_INSTALL_PREFIX "../install")

# setting up clang as default tool chain
set(CMAKE_C_COMPILER             "/usr/bin/clang")
set(CMAKE_C_FLAGS                "-Wall -std=c99")
set(CMAKE_C_FLAGS_DEBUG          "-g")
set(CMAKE_C_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
set(CMAKE_C_FLAGS_RELEASE        "-O3 -DNDEBUG")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g")

set(CMAKE_CXX_COMPILER             "/usr/bin/clang++")
set(CMAKE_CXX_FLAGS                "-Wall -std=c++2a")
set(CMAKE_CXX_FLAGS_DEBUG          "-g")
set(CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE        "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")

set(_CMAKE_TOOLCHAIN_PREFIX "llvm-")

set(CMAKE_CXX_CLANG_TIDY 
    "clang-tidy;-checks=*,-fuchsia*" )