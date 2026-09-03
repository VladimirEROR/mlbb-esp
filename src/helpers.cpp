#include <stdio.h>
#include <math.h>
#include "offsets.h"

struct Vector3 { float x, y, z; };

Vector3 WorldToScreen(Vector3 worldPos, void* camera) {
    Vector3 result = {0, 0, 0};
    if (!camera) return result;

    typedef Vector3 (*WorldToScreenFunc)(void*, Vector3);
    WorldToScreenFunc wts = (WorldToScreenFunc)Camera_WorldToScreenPoint;
    result = wts(camera, worldPos);

    float height = GetScreenHeight();
    result.y = height - result.y;

    return result;
}

float GetScreenWidth() {
    typedef int (*GetWidthFunc)();
    GetWidthFunc getWidth = (GetWidthFunc)Screen_get_width;
    return (float)getWidth();
}

float GetScreenHeight() {
    typedef int (*GetHeightFunc)();
    GetHeightFunc getHeight = (GetHeightFunc)Screen_get_height;
    return (float)getHeight();
}

// ===== Unity GL Drawing (example, must be adapted)
void DrawBox(float x1, float y1, float x2, float y2, float r, float g, float b, float a) {
    // Implement via Unity GL or GUI
    // For iOS, you'd use GL.Begin(GL.LINES) etc.
}

void DrawHealthBar(float x, float y, float w, float h, float percent) {
    DrawBox(x, y, x + w, y + h, 0.2f, 0.2f, 0.2f, 1.0f);
    DrawBox(x, y, x + w * percent, y + h, 0.0f, 1.0f, 0.0f, 1.0f);
}

void DrawText(const char* text, float x, float y, float r, float g, float b, float a) {
    // Implement via Unity GUI.Label
}

void* GetBattleManagerInstance() {
    static void* instance = nullptr;
    if (!instance) {
        // Find BattleManager singleton
        // Usually BattleManager.get_instance() or a static field
    }
    return instance;
}
