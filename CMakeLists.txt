cmake_minimum_required(VERSION 3.17.3)

project(DebArchiveExtractor)

set(CMAKE_CXX_STANDARD 20)

add_executable(DebArchiveExtractor)

target_sources(DebArchiveExtractor PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp)

target_include_directories(DebArchiveExtractor PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)

target_compile_options(DebArchiveExtractor PRIVATE
        -Wall -Wextra -Wconversion -Wpedantic -O0 -g3)

set(CPM_DOWNLOAD_VERSION "v0.40.0")
include(${CMAKE_CURRENT_LIST_DIR}/cmake/install_cpm_if_not_available.cmake)
unset(CPM_DOWNLOAD_VERSION)

include(${CMAKE_CURRENT_LIST_DIR}/cmake/install_cpm_packages.cmake)

target_link_libraries(DebArchiveExtractor PRIVATE
        fmt::fmt
)