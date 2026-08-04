#include <iostream>

#include "core/render.h"
#include <glad/gl.h>
#include <GLFW/glfw3.h>


#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int main(){

    // 初始化glfw
    if (!glfwInit())
    {
        std::fprintf(stderr, "[casteljau]" ANSI_COLOR_RED " GLFW 初始化失敗！" ANSI_COLOR_RESET "\n");
        std::fprintf(stderr, "[casteljau]" ANSI_COLOR_RED " GLFW initialization failed!" ANSI_COLOR_RESET "\n");
        return -1;
    }
    std::fprintf(stderr, "[casteljau]" ANSI_COLOR_GREEN " GLFW 初始化成功！" ANSI_COLOR_RESET "\n");
    
     // Request OpenGL 3.3 Core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

// #ifdef __APPLE__
//     glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
// #endif
    // 設定視窗
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

    // 建立視窗
    GLFWwindow* window = glfwCreateWindow(800, 600, "標題", nullptr, nullptr);
    if(!window)
    {
        std::fprintf(stderr, "[casteljau]" ANSI_COLOR_RED " 視窗建立失敗！" ANSI_COLOR_RESET "\n");
        std::fprintf(stderr, "[casteljau]" ANSI_COLOR_RED " Window creation failed!" ANSI_COLOR_RESET "\n");
        glfwTerminate();
        return -1;
    }
    
}