#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <vector>
#include <algorithm>
#include "offsets.h"

extern "C" {
    void* (*Il2CppGetFieldOffset)(const char*, const char*, const char*, const char*) = nullptr;
    void* (*Il2CppGetMethodOffset)(const char*, const char*, const char*, const char*, int) = nullptr;
}

// ===== Structs
struct Vector3 { float x, y, z; };

struct Entity {
    void* ptr;
    Vector3 pos;
    float hp, hpMax;
    bool isDead;
    bool isEnemy;
    int level;
    uint32_t id;
    char* name;
};

// ===== Globals
std::vector<Entity> entities;
pthread_mutex_t entityMutex = PTHREAD_MUTEX_INITIALIZER;
void* localPlayerPtr = nullptr;
void* cameraPtr = nullptr;
bool espEnabled = true;  // Toggle state

// ===== Forward declarations
Vector3 WorldToScreen(Vector3 world, void* cam);
float GetScreenWidth();
float GetScreenHeight();
void DrawBox(float x1, float y1, float x2, float y2, float r, float g, float b, float a);
void DrawHealthBar(float x, float y, float w, float h, float percent);
void DrawText(const char* text, float x, float y, float r, float g, float b, float a);
void* GetBattleManagerInstance();
void DrawToggleButton();

// ===== Update entities
void UpdateEntities() {
    void* bm = GetBattleManagerInstance();
    if (!bm) return;

    localPlayerPtr = *(void**)((uintptr_t)bm + BattleManager_m_LocalPlayerShow);

    void* playersArray = *(void**)((uintptr_t)bm + BattleManager_m_ShowPlayers);
    if (!playersArray) return;

    int length = *(int*)((uintptr_t)playersArray + Array_length);
    void** items = (void**)((uintptr_t)playersArray + Array_items);

    pthread_mutex_lock(&entityMutex);
    entities.clear();

    for (int i = 0; i < length; i++) {
        void* player = items[i];
        if (!player) continue;

        Entity ent;
        ent.ptr = player;
        ent.pos = *(Vector3*)((uintptr_t)player + ShowEntity__Position);
        ent.hp = *(float*)((uintptr_t)player + EntityBase_m_Hp);
        ent.hpMax = *(float*)((uintptr_t)player + EntityBase_m_HpMax);
        ent.isDead = *(bool*)((uintptr_t)player + EntityBase_m_bDeath);
        bool sameCamp = *(bool*)((uintptr_t)player + EntityBase_m_bSameCampType);
        ent.isEnemy = !sameCamp;
        ent.level = *(int*)((uintptr_t)player + EntityBase_m_Level);
        ent.id = *(uint32_t*)((uintptr_t)player + EntityBase_m_ID);
        ent.name = (char*)((uintptr_t)player + ShowEntity_m_RoleName);

        if (player == localPlayerPtr || ent.isDead) continue;
        entities.push_back(ent);
    }

    pthread_mutex_unlock(&entityMutex);
}

// ===== Draw ESP
void DrawESP() {
    if (!espEnabled) return;

    void* cam = cameraPtr;
    if (!cam) {
        typedef void* (*GetMainCamera_t)();
        GetMainCamera_t get_main = (GetMainCamera_t)Camera_get_main;
        cam = get_main();
        cameraPtr = cam;
    }
    if (!cam) return;

    float screenW = GetScreenWidth();
    float screenH = GetScreenHeight();

    pthread_mutex_lock(&entityMutex);
    for (auto& ent : entities) {
        if (!ent.isEnemy) continue;

        Vector3 screenPos = WorldToScreen(ent.pos, cam);
        if (screenPos.z < 0.01f) continue;
        if (screenPos.x < 0 || screenPos.x > screenW) continue;
        if (screenPos.y < 0 || screenPos.y > screenH) continue;

        float dist = screenPos.z;
        float boxSize = 120.0f / (dist + 0.1f);
        if (boxSize < 10.0f) boxSize = 10.0f;
        if (boxSize > 150.0f) boxSize = 150.0f;

        float half = boxSize / 2.0f;
        float top = screenPos.y - boxSize;
        float bottom = screenPos.y + boxSize;
        float left = screenPos.x - half;
        float right = screenPos.x + half;

        DrawBox(left, top, right, bottom, 1.0f, 0.0f, 0.0f, 1.0f);

        float hpPercent = ent.hp / ent.hpMax;
        float barW = boxSize * 0.8f;
        float barX = screenPos.x - barW / 2.0f;
        float barY = bottom + 4.0f;
        DrawHealthBar(barX, barY, barW, 4.0f, hpPercent);

        char label[256];
        const char* name = ent.name ? ent.name : "??";
        sprintf(label, "%s [%.0fm]", name, dist * 0.3f);
        DrawText(label, screenPos.x, top - 16, 1.0f, 1.0f, 1.0f, 1.0f);
    }
    pthread_mutex_unlock(&entityMutex);
}

// ===== Hook BattleManager.Update
void* HookedUpdate(void* battleManager) {
    typedef void* (*UpdateFunc_t)(void*);
    UpdateFunc_t originalUpdate = (UpdateFunc_t)BattleManager_Update;
    void* result = originalUpdate(battleManager);

    UpdateEntities();
    DrawESP();
    DrawToggleButton();

    return result;
}

// ===== Init
extern "C" void mlbb_esp_init() {
    // Hook BattleManager.Update
    // MSHookFunction((void*)BattleManager_Update, (void*)HookedUpdate, (void**)&originalUpdate);
    printf("[ESP] Injected. Press the button to toggle.\n");
}
