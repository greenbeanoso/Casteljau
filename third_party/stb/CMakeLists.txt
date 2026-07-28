cmake_minimum_required(VERSION 3.15)

project(third_party LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(FetchContent)


FetchContent_Declare(
    stb_source
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG master
    GIT_SHALLOW TRUE
)


FetchContent_MakeAvailable(stb_source)


FetchContent_GetProperties(stb_source)

add_library(stb_lib STATIC
    stb_impl.cpp
)


target_include_directories(stb_lib
    PUBLIC
        ${stb_source_SOURCE_DIR}
)