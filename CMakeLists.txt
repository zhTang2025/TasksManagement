cmake_minimum_required(VERSION 3.20.0)
project(Tasks_Management)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)
add_library(common SHARED ${SRC_LIST})
target_include_directories(common PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(a main.cpp)
target_include_directories(a PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(a PUBLIC common)