#include <iostream>

#include <vector>
#include <memory>
#include <string>

#include "WindowManager.h"



void WindowManager::add(std::unique_ptr<PanelContainer> panelContainerPtr) { 
    if (!panelContainerPtr) return; // 安全檢查，避免解引用空指標
    Panels.push_back(std::move(panelContainerPtr)); 
}

PanelContainer* WindowManager::getPanelPtr(int index) { //TODO Refactor
    if (index < 0 || index >= Panels.size()) {
        std::cerr << "Index out of bounds: " << index << std::endl;
        return nullptr; // 返回空指針表示索引無效
    }
    return Panels[index].get();
}