// ===== WindowManager.h =====
#pragma once
#include "WindowTypes.h"   // 引入上面定義的 Panel 和 PanelType
#include <unordered_map>



class WindowManager {
public:
    void add(std::unique_ptr<PanelContainer> panelContainerPtr);
    PanelContainer* getPanelPtr(int index);
private:
    std::vector<std::unique_ptr<PanelContainer>> Panels;
};