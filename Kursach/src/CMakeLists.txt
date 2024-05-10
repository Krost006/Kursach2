CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

set(SOURCES application.cpp base.cpp support.cpp)
add_library(sources SHARED ${SOURCES})

target_include_directories(sources PRIVATE ${PROJECT_SOURCE_DIR}/include)