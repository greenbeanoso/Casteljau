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
    
    // 設定視窗
     // Request OpenGL 3.3 Core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // #ifdef __APPLE__ //現版本在開發上不考慮其他平台
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE); // macOS 需要這行
    // #endif

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
    std::fprintf(stderr, "[casteljau]" ANSI_COLOR_GREEN " 視窗建立成功！" ANSI_COLOR_RESET "\n");
    // 載入 glad(openGL function loader)
    glfwMakeContextCurrent(window);
    int glVersion = gladLoadGL(glfwGetProcAddress);
    if (glVersion == 0)
    {
        std::fprintf(stderr, "[casteljau]" ANSI_COLOR_RED " Glad載入失敗！" ANSI_COLOR_RESET "\n");
        std::fprintf(stderr, "[casteljau]" ANSI_COLOR_RED " Glad loading failed!" ANSI_COLOR_RESET "\n");
        glfwTerminate(); //銷毀視窗
        return -1;
    }
    std::fprintf(stderr, "[casteljau]" ANSI_COLOR_GREEN "載入 OpenGL %d.%d\n" ANSI_COLOR_RESET "\n", GLAD_VERSION_MAJOR(glVersion), GLAD_VERSION_MINOR(glVersion));

    // 主迴圈
    while (!glfwWindowShouldClose(window))
    {
        // 清除顏色緩衝區
        glClear(GL_COLOR_BUFFER_BIT);

        // 這裡可以放置渲染代碼

        // 交換前後緩衝區
        glfwSwapBuffers(window);

        // 處理事件
        glfwPollEvents();
    }

}