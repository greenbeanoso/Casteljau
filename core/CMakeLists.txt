cmake_minimum_required(VERSION 3.15)

project(core LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#=======================================================
# core library
#=======================================================

add_library(core STATIC)


target_sources(core
    PRIVATE
        src/render.cpp
)
target_link_libraries(core
    PUBLIC
        glm::glm
        stb_lib
        glfw
)

# 給其他 target 使用 core 的 header
target_include_directories(core
    PUBLIC
        include
)

#=======================================================
# Output
#=======================================================

set_target_properties(core PROPERTIES

    ARCHIVE_OUTPUT_DIRECTORY
        ${CMAKE_BINARY_DIR}/lib

)