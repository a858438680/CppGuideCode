cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS FALSE)

project(CppGuide)

add_subdirectory(${CMAKE_SOURCE_DIR}/RAII)

add_subdirectory(${CMAKE_SOURCE_DIR}/String)

add_subdirectory(${CMAKE_SOURCE_DIR}/Rvalue)

add_subdirectory(${CMAKE_SOURCE_DIR}/Callable)

add_subdirectory(${CMAKE_SOURCE_DIR}/Atomic)

add_subdirectory(${CMAKE_SOURCE_DIR}/SmartPointer)

add_subdirectory(${CMAKE_SOURCE_DIR}/Patterns)

add_subdirectory(${CMAKE_SOURCE_DIR}/Execution)
