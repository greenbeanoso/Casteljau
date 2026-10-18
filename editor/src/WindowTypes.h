// ===== WindowTypes.h =====
#pragma once   // 防止這個檔案被重複 include
#include <cstdint>
#include <string>
#include <memory>
#include <vector>
#include <any>

enum class PanelType{
    Dock,
    Viewport,
};
struct PanelContainer {
    virtual PanelType type() const = 0;
    virtual ~PanelContainer() = default;
};


// Dock
enum class SplitDirection {
    None,        // 葉節點，即真正的 Panel
    Horizontal,  // 左右分割
    Vertical     // 上下分割
};
struct DockData : public PanelContainer {

    PanelType type() const override { return PanelType::Dock; }
    PanelContainer* planelA = nullptr;
    PanelContainer* planelB = nullptr;
    float split_ratio;
    SplitDirection direction;
};


// Viewport
struct ViewportData : public PanelContainer {
    PanelType type() const override { return PanelType::Viewport; }
    int* Scene;

    int x;
    int y;
    int z;
    // Rotate with Euler Angles
    float Rx; //Pitch
    float Ry; //Yaw
    float Rz; //Roll
    // Focal Length
    int f;
};