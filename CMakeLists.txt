cmake_minimum_required(VERSION 2.6)
project(cpp_external_processes CXX)

add_library(external_processes ext_proc.cpp)

find_package (Threads)
target_link_libraries (external_processes ${CMAKE_THREAD_LIBS_INIT})

target_include_directories(external_processes
	PUBLIC ${PROJECT_SOURCE_DIR}/
)

