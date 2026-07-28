cmake_minimum_required(VERSION 3.15) #Cmake最低版本要求

project(editor LANGUAGES C CXX) 

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
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL        OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(glfw)

#=======================================================
# -----------------------------------------------------------------------------
# 建立執行檔
# -----------------------------------------------------------------------------
add_executable(editor
    src/main.cpp
)

# 連結 glfw
#   glfw           -> GLFW 官方 CMake 提供的 target
target_link_libraries(editor PRIVATE glfw core)

# -----------------------------------------------------------------------------
# 連結作業系統的 OpenGL 函式庫
# 因為我們沒有使用 GLAD / GLEW 這種 Loader，而是直接呼叫系統標頭檔
# （GLFW 會自動 #include 對應平台的 gl.h），所以要手動連結 OpenGL 函式庫本身。
# -----------------------------------------------------------------------------
if(APPLE)
    # macOS 上 OpenGL 是一個 Framework
    target_link_libraries(editor PRIVATE "-framework OpenGL")
elseif(WIN32)
    # Windows 上 OpenGL 函式庫叫 opengl32
    target_link_libraries(editor PRIVATE opengl32)
else()
    # Linux / 其他類 Unix 系統，用 CMake 內建的 FindOpenGL 模組
    find_package(OpenGL REQUIRED)
    target_link_libraries(editor PRIVATE OpenGL::GL)
endif()

# 把編譯出來的執行檔放到 build 目錄的根目錄下，方便執行
set_target_properties(editor PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)