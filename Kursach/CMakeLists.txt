CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
project(tree_system)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

add_executable(main main.cpp)

add_subdirectory(src)
target_link_libraries(main PRIVATE sources)
target_include_directories(main PRIVATE ${PROJECT_SOURCE_DIR}/include)