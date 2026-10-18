cmake_minimum_required(VERSION 3.20)
project(MyEngineProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#=======================================================
include(FetchContent)
#-------------------------------------------------------
# FetchContent：CMake 內建的工具，可以在設定（configure）階段自動從 GitHub
# 把原始碼抓下來，不需要使用者事先手動安裝這些函式庫。
#-------------------------------------------------------
#glfw - 負責視窗建立 / 輸入事件 / OpenGL context
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.4          # 使用穩定的 3.4 版本
    GIT_SHALLOW    TRUE
)

# 關掉 GLFW 自帶的範例、測試、文件編譯，我們只需要函式庫本身，可以加快編譯速度
# set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
# set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
# set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
# set(GLFW_INSTALL        OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(glfw)

#glm - 負責數學運算（向量、矩陣、四元數）
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG        1.0.1
    GIT_SHALLOW    TRUE
)

FetchContent_MakeAvailable(glm)


add_subdirectory(third_party)
add_subdirectory(core)
add_subdirectory(editor)

