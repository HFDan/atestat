cmake_minimum_required(VERSION 3.28)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_COLOR_MAKEFILE ON)
project(tui++)

set(CMAKE_CXX_STANDARD 20)
option(TUIPP_BUILD_SHARED "Whether to build tui as a shared or static library" OFF)

file(GLOB_RECURSE TUIPP_SOURCES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/*.cc")
if (${TUIPP_BUILD_SHARED})
    add_library(tui++ SHARED ${TUIPP_SOURCES})
    set_target_properties(tui++ PROPERTIES VERSION 0.0.1 SOVERSION 1)
else()
    add_library(tui++ STATIC ${TUIPP_SOURCES})
endif()
target_include_directories(tui++ PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(test test.cc)
target_link_libraries(test PUBLIC tui++)
