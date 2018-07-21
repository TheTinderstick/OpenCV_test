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





