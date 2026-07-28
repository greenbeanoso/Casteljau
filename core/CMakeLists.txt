cmake_minimum_required(VERSION 3.15)

project(core LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(FetchContent)


#=======================================================
# GLM
#=======================================================

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG        1.0.1
    GIT_SHALLOW    TRUE
)

FetchContent_MakeAvailable(glm)



#=======================================================
# core library
#=======================================================

add_library(core STATIC)


target_sources(core
    PRIVATE
        src/render.cpp
)


target_include_directories(core
    PUBLIC
        include
)


target_link_libraries(core
    PUBLIC
        glm::glm
        stb_lib
)



#=======================================================
# Output
#=======================================================

set_target_properties(core PROPERTIES

    ARCHIVE_OUTPUT_DIRECTORY
        ${CMAKE_BINARY_DIR}/lib

)