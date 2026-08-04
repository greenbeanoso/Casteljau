/*
 * glfw_demo.cpp
 * -----------------------------------------------------------------------
 * 這是一個「單檔案」示範程式,目的是把 GLFW 常用的函式盡量都用一次,
 * 讓你可以對照官方文件 (https://www.glfw.org/docs/latest/) 邊看邊測試。
 *
 * 涵蓋的功能:
 *   1. 初始化與視窗建立 (glfwInit / glfwWindowHint / glfwCreateWindow)
 *   2. Context 綁定與 GLAD 載入 (glfwMakeContextCurrent / gladLoadGL)
 *   3. 鍵盤輸入 - 兩種方式: callback 與 polling
 *   4. 滑鼠按鍵輸入 callback
 *   5. 滑鼠游標位置 callback
 *   6. 滑鼠捲動 (scroll) callback
 *   7. 視窗大小改變 callback (framebuffer resize)
 *   8. 視窗關閉旗標 (glfwWindowShouldClose / glfwSetWindowShouldClose)
 *   9. 計時 (glfwGetTime) 與 vsync (glfwSwapInterval)
 *  10. 標題列動態更新 (glfwSetWindowTitle)
 *
 * 編譯方式 (以 g++ + Linux/pkg-config 為例,實際依你的專案結構調整):
 *   g++ glfw_demo.cpp glad.c -o glfw_demo -lglfw -ldl
 *
 * 若用 CMake,概念上是:
 *   target_link_libraries(glfw_demo PRIVATE glfw OpenGL::GL)
 * -----------------------------------------------------------------------
 */

#include <glad/gl.h>      // 必須在 GLFW header 之前 include,見前面對話中的說明
#include <GLFW/glfw3.h>

#include <cstdio>
#include <cmath>

// -------------------------------------------------------------------------
// 全域狀態(教學範例圖方便直接用全域變數,實際專案建議包成 class 或用
// glfwSetWindowUserPointer 把狀態掛在 window 上,詳見文末補充說明)
// -------------------------------------------------------------------------
static float g_clearColor[3] = { 0.10f, 0.10f, 0.15f }; // 背景色,會被滑鼠左鍵點擊改變
static double g_lastMouseX = 0.0, g_lastMouseY = 0.0;   // 記錄游標位置

// -------------------------------------------------------------------------
// Callback 1: 鍵盤事件
// 觸發時機: 按下 (GLFW_PRESS)、放開 (GLFW_RELEASE)、長按重複觸發 (GLFW_REPEAT)
// -------------------------------------------------------------------------
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // ESC 鍵按下時,設定「應該關閉」旗標,主迴圈偵測到後會自然結束
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    if (action == GLFW_PRESS)
    {
        // 只印出「剛按下」的那一瞬間,避免長按洗版
        std::printf("[keyboard] key pressed: scancode=%d, mods=%d\n", scancode, mods);
    }
}

// -------------------------------------------------------------------------
// Callback 2: 滑鼠按鍵事件
// button: GLFW_MOUSE_BUTTON_LEFT / RIGHT / MIDDLE ...
// -------------------------------------------------------------------------
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        // 左鍵點擊時,把背景色換成跟游標位置相關的顏色,做一個「有反應」的效果
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        g_clearColor[0] = static_cast<float>(g_lastMouseX / width);
        g_clearColor[1] = static_cast<float>(g_lastMouseY / height);
        g_clearColor[2] = 0.4f;

        std::printf("[mouse] left button clicked at (%.1f, %.1f)\n", g_lastMouseX, g_lastMouseY);
    }

    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        std::printf("[mouse] right button clicked\n");
    }
}

// -------------------------------------------------------------------------
// Callback 3: 滑鼠游標位置事件
// xpos, ypos 是相對於視窗內容區域左上角的座標(單位是螢幕座標,不一定等於像素)
// -------------------------------------------------------------------------
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    g_lastMouseX = xpos;
    g_lastMouseY = ypos;
    // 這個 callback 觸發頻率很高,故意不印 log,避免洗版;
    // 如果要觀察,可以取消下面這行註解
    // std::printf("[mouse] move to (%.1f, %.1f)\n", xpos, ypos);
}

// -------------------------------------------------------------------------
// Callback 4: 滑鼠捲動事件
// yoffset: 垂直捲動量(滑鼠滾輪),xoffset: 水平捲動量(觸控板常見)
// -------------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    std::printf("[mouse] scroll offset = (%.2f, %.2f)\n", xoffset, yoffset);
}

// -------------------------------------------------------------------------
// Callback 5: framebuffer 大小改變事件
// 使用者拖曳視窗邊框、或在高 DPI 螢幕縮放時會觸發。
// 注意: 這裡拿到的是「framebuffer 像素大小」,跟 glfwSetWindowSizeCallback
// 拿到的「視窗大小(螢幕座標)」在高 DPI 螢幕上可能不一樣,渲染要用這個。
// -------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    std::printf("[window] framebuffer resized to %d x %d\n", width, height);
}

// -------------------------------------------------------------------------
// GLFW 錯誤回報 callback:與其讓 glfwInit 或 glfwCreateWindow 失敗後
// 只回傳 NULL/FALSE 讓你猜原因,不如設定這個拿到實際錯誤訊息。
// 建議在 glfwInit() 之前就設定。
// -------------------------------------------------------------------------
void error_callback(int error_code, const char* description)
{
    std::fprintf(stderr, "[glfw error] (%d) %s\n", error_code, description);
}

// -------------------------------------------------------------------------
// polling 方式讀取鍵盤狀態(跟 callback 方式不同,這是「主動詢問目前狀態」,
// 適合用在「持續移動」這種需要每一幀都檢查的情境,例如 WASD 移動角色)
// -------------------------------------------------------------------------
void process_input_by_polling(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        std::printf("[polling] W is currently held down\n");
    }
}

int main()
{
    // ---------------------------------------------------------------
    // 1. 設定錯誤 callback(愈早設定愈好,能攔到初始化階段的錯誤)
    // ---------------------------------------------------------------
    glfwSetErrorCallback(error_callback);

    // ---------------------------------------------------------------
    // 2. 初始化 GLFW
    // ---------------------------------------------------------------
    if (!glfwInit())
    {
        std::fprintf(stderr, "glfwInit failed\n");
        return -1;
    }

    // ---------------------------------------------------------------
    // 3. 設定要建立的 context 規格(必須在 glfwCreateWindow 之前)
    // ---------------------------------------------------------------
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE); // macOS 需要這行
#endif

    // ---------------------------------------------------------------
    // 4. 建立視窗 + context
    // ---------------------------------------------------------------
    GLFWwindow* window = glfwCreateWindow(800, 600, "GLFW Demo", nullptr, nullptr);
    if (!window)
    {
        std::fprintf(stderr, "glfwCreateWindow failed\n");
        glfwTerminate();
        return -1;
    }

    // ---------------------------------------------------------------
    // 5. 註冊各種 callback(在 MakeContextCurrent 之前之後都可以設定,
    //    callback 註冊本身跟 context 無關,只是跟 window handle 綁定)
    // ---------------------------------------------------------------
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // ---------------------------------------------------------------
    // 6. 把這個視窗的 context 設為目前執行緒的當前 context
    // ---------------------------------------------------------------
    glfwMakeContextCurrent(window);

    // ---------------------------------------------------------------
    // 7. 載入 OpenGL 函式指標(必須在 MakeContextCurrent 之後)
    // ---------------------------------------------------------------
    // ❌ glad1 寫法,你的 gl.h 沒有這個函式
    // if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    // {
    //     std::fprintf(stderr, "gladLoadGLLoader failed\n");
    //     glfwTerminate();
    //     return -1;
    // }
    // ✅ glad2 寫法,對應你這份 gl.h
    int glVersion = gladLoadGL(glfwGetProcAddress);
    if (glVersion == 0)
    {
        std::fprintf(stderr, "gladLoadGL failed\n");
        glfwTerminate();
        return -1;
    }
    std::printf("Loaded OpenGL %d.%d\n", GLAD_VERSION_MAJOR(glVersion), GLAD_VERSION_MINOR(glVersion));

    // ---------------------------------------------------------------
    // 8. 開啟垂直同步(1 = 每次畫面更新等待一個螢幕刷新週期,避免 tearing)
    // ---------------------------------------------------------------
    glfwSwapInterval(1);

    // 手動觸發一次 framebuffer size callback 的邏輯,確保初始 viewport 正確
    int initialWidth, initialHeight;
    glfwGetFramebufferSize(window, &initialWidth, &initialHeight);
    glViewport(0, 0, initialWidth, initialHeight);

    double lastTitleUpdateTime = glfwGetTime();
    int frameCount = 0;

    // ---------------------------------------------------------------
    // 9. 主迴圈 (render loop)
    // ---------------------------------------------------------------
    while (!glfwWindowShouldClose(window))
    {
        // 9-1. polling 方式的輸入檢查,每一幀都問一次目前狀態
        process_input_by_polling(window);

        // 9-2. 清除畫面,顏色來自全域變數(會被滑鼠左鍵點擊改變,見 callback)
        glClearColor(g_clearColor[0], g_clearColor[1], g_clearColor[2], 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 9-3. (實際專案會在這裡呼叫 glDrawArrays / glDrawElements 等繪圖指令)

        // 9-4. 把後緩衝區 (back buffer) 交換到螢幕上顯示
        glfwSwapBuffers(window);

        // 9-5. 處理累積的事件佇列,觸發上面註冊的各種 callback
        glfwPollEvents();

        // 9-6. 每秒更新一次標題列,顯示 FPS(順便示範 glfwSetWindowTitle 用法)
        frameCount++;
        double now = glfwGetTime();
        if (now - lastTitleUpdateTime >= 1.0)
        {
            char title[64];
            std::snprintf(title, sizeof(title), "GLFW Demo - %d FPS", frameCount);
            glfwSetWindowTitle(window, title);
            frameCount = 0;
            lastTitleUpdateTime = now;
        }
    }

    // ---------------------------------------------------------------
    // 10. 收尾: 銷毀視窗、終止函式庫
    //     (glfwTerminate 本身就會銷毀所有還存在的視窗,
    //      但顯式呼叫 glfwDestroyWindow 是比較清楚的寫法)
    // ---------------------------------------------------------------
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

/*
 * -----------------------------------------------------------------------
 * 補充說明(文件之外、實務上常見的疑問)
 * -----------------------------------------------------------------------
 *
 * Q1. callback 跟 polling 該用哪個?
 *     - callback (glfwSetXxxCallback): 適合「事件性」輸入,例如按一下滑鼠、
 *       按一下按鍵、捲動一下。只在「狀態改變的那一瞬間」被呼叫一次。
 *     - polling (glfwGetKey / glfwGetMouseButton): 適合「連續性」輸入,
 *       例如 WASD 移動角色 —— 你需要每一幀都知道「現在」是不是被按著,
 *       而不是只在按下瞬間知道一次。
 *
 * Q2. 為什麼很多教學會用 glfwSetWindowUserPointer 而不是全域變數?
 *     因為 callback 函式的簽章是固定的 (GLFW 規定的),沒有辦法直接塞入
 *     你自己的 class 實例。解法是用 glfwSetWindowUserPointer(window, this)
 *     把你的物件指標「掛」在 window 上,再於 callback 內用
 *     glfwGetWindowUserPointer(window) 拿回來、轉型使用。本範例為了單檔案
 *     教學單純,直接用了全域變數,實際專案建議改用這個機制。
 *
 * Q3. gladLoadGL(glfwGetProcAddress) 跟這裡用的
 *     gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) 差在哪?
 *     這是 GLAD 版本差異: 新版 glad2 產生的程式碼函式名稱是 gladLoadGL
 *     (直接吃函式指標型別),舊版 glad (glad.generator 產生、教學最常見的
 *     那份) 是 gladLoadGLLoader,吃的是 GLADloadproc 型別,需要強制轉型。
 *     實際使用時,以你自己專案裡 glad.h 產生出來的函式簽章為準。
 * -----------------------------------------------------------------------
 */