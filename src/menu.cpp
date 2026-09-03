#include "imgui/imgui.h"
#include "imgui/imgui_impl_metal.h"
#include "imgui/imgui_impl_objc.h"
#include <UIKit/UIKit.h>
#include <Metal/Metal.h>
#include <QuartzCore/QuartzCore.h>

struct MenuState {
    bool espEnabled = true;
    float boxColor[3] = {1.0f, 0.0f, 0.0f};
    bool showHealthBar = true;
    bool showDistance = true;
    float fov = 60.0f;
    bool aimbotEnabled = false;
} g_Menu;

static id<MTLDevice> g_MetalDevice = nil;
static id<MTLCommandQueue> g_MetalCommandQueue = nil;
static CAMetalLayer* g_MetalLayer = nil;

void InitImGui() {
    g_MetalDevice = MTLCreateSystemDefaultDevice();
    g_MetalCommandQueue = [g_MetalDevice newCommandQueue];

    UIWindow* window = [[UIApplication sharedApplication] keyWindow];
    UIView* rootView = window.rootViewController.view;
    g_MetalLayer = [CAMetalLayer layer];
    g_MetalLayer.device = g_MetalDevice;
    g_MetalLayer.pixelFormat = MTLPixelFormatBGRA8Unorm;
    g_MetalLayer.framebufferOnly = YES;
    g_MetalLayer.frame = rootView.bounds;
    [rootView.layer addSublayer:g_MetalLayer];

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplMetal_Init(g_MetalDevice);
    ImGui_ImplObjC_Init();
}

void RenderMenu() {
    ImGui_ImplMetal_NewFrame(g_MetalLayer);
    ImGui_ImplObjC_NewFrame();
    ImGui::NewFrame();

    ImGui::SetNextWindowBgAlpha(0.7f);
    ImGui::Begin("MLBB ESP", nullptr, ImGuiWindowFlags_NoCollapse);

    ImGui::Text("★ ESP Controller ★");
    ImGui::Separator();

    ImGui::Checkbox("ESP Enabled", &g_Menu.espEnabled);
    ImGui::ColorEdit3("Box Color", g_Menu.boxColor);
    ImGui::Checkbox("Health Bars", &g_Menu.showHealthBar);
    ImGui::Checkbox("Show Distance", &g_Menu.showDistance);
    ImGui::SliderFloat("FOV", &g_Menu.fov, 20.0f, 120.0f);
    ImGui::Checkbox("Aimbot (Soft)", &g_Menu.aimbotEnabled);

    ImGui::Separator();
    ImGui::Text("Status: %s", g_Menu.espEnabled ? "ACTIVE" : "DISABLED");
    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);

    ImGui::End();

    ImGui::Render();

    id<MTLCommandBuffer> commandBuffer = [g_MetalCommandQueue commandBuffer];
    ImGui_ImplMetal_RenderDrawData(ImGui::GetDrawData(), commandBuffer);
    [commandBuffer presentDrawable:g_MetalLayer.nextDrawable];
    [commandBuffer commit];
}
