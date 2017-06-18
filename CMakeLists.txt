cmake_minimum_required(VERSION 3.7)
project(MemoryManager)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp MemoryManager.cpp MemoryManager.h MemorySlab.cpp MemorySlab.h Process.cpp Process.h)
add_executable(MemoryManager ${SOURCE_FILES})