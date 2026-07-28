cmake_minimum_required(VERSION 3.20)
project(MyEngineProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_subdirectory(third_party/stb)
add_subdirectory(core)
add_subdirectory(editor)
