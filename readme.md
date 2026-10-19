⚠️ **Status: Heavily Work-in-Progress (Pre-MVP)**
# Casteljau
這是一個基於**德卡斯特里奧算法(De Casteljau's algorithm)**或是說**貝茲曲線(Bézier curve)**為核心的電腦繪圖應用生態系
*   **應用層:**(依賴於Core的前端系統)
    * Editor 
*   **核心層(Core):**
    *   不進行 Draw Call
    *   向上層應用提供整理好的物理/幾何**向量 (Vectors)** 與**變換矩陣 (Matrices)**
*   **基礎第三方依賴 (Third-Party)**
    *   `GLFW` + `GLAD` (視窗與 OpenGL 載入)
    *   `GLM` + `STB` (數學運算與圖片解碼)

## 🛠️ 開發環境與建置 (Development Setup)

本專案使用 **CMake** 作為建置工具。

### 驗證環境 (Verified Environment)
*   **OS**: Arch Linux + Hyprland(目前主要開發與測試平台)