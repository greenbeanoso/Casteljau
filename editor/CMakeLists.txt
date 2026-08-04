cmake_minimum_required(VERSION 3.15) #Cmake最低版本要求

project(editor LANGUAGES C CXX) 

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# -----------------------------------------------------------------------------
# 建立執行檔
# -----------------------------------------------------------------------------
add_executable(editor
    src/main.cpp
)

# 連結
target_link_libraries(editor PRIVATE core glfw glad)
