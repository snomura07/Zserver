cmake_minimum_required(VERSION 3.5)
project(Zserver)

# C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# install prefix
set(CMAKE_INSTALL_PREFIX /var/opt/zserver/)

# common include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/protobuf
    ${CMAKE_SOURCE_DIR}/common
    ${CMAKE_SOURCE_DIR}/utils
)

add_subdirectory(core)
add_subdirectory(common)
# add_subdirectory(protobuf)
# add_subdirectory(test)
