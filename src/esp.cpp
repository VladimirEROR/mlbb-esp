#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <vector>
#include <algorithm>
#include "offsets.h"

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

std::vector<Entity> entities;
pthread_mutex_t entityMutex = PTHREAD_MUTEX_INITIALIZER;
void* localPlayerPtr = nullptr;
void* cameraPtr = nullptr;
bool espEnabled = true;

// ===== Forward declarations
Vector3 WorldToScreen(Vector3 world, void* cam);
float GetScreenWidth();
float GetScreenHeight();
void DrawBox(float x1, float y1, float x2, float y2, float r, float g, float b, float a);
void DrawHealthBar(float x, float y, float w, float h, float percent);
void DrawText(const char* text, float x, float y, float r, float g, float b, float a);
void* GetBattleManagerInstance();

// ===== Safe pointer read
template<typename T>
T SafeRead(void* addr, T fallback = T()) {
    if (!addr) return fallback;
    // Check if address looks valid (crude but prevents 0x19999998 crashes)
    uintptr_t val = (uintptr_t)addr;
    if (val < 0x1000 || val > 0x7fffffffffffULL) return fallback;
    return *(T*)addr;
}

void UpdateEntities() {
    void* bm = GetBattleManagerInstance();
    if (!bm) {
        printf("[ESP] BattleManager is null\n");
        return;
    }

    // Read local player with safety
    localPlayerPtr = SafeRead<void*>( (void**)((uintptr_t)bm + BattleManager_m_LocalPlayerShow) );
    if (!localPlayerPtr) {
        printf("[ESP] LocalPlayer is null\n");
    }

    // Read players array
    void* playersArray = SafeRead<void*>( (void**)((uintptr_t)bm + BattleManager_m_ShowPlayers) );
    if (!playersArray) {
        printf("[ESP] Players array is null\n");
        return;
    }

    int length = SafeRead<int>( (int*)((uintptr_t)playersArray + Array_length), 0 );
    if (length <= 0 || length > 100) {  // sanity check
        printf("[ESP] Invalid array length: %d\n", length);
        return;
    }

    void** items = (void**)((uintptr_t)playersArray + Array_items);
    if (!items) return;

    pthread_mutex_lock(&entityMutex);
    entities.clear();

    for (int i = 0; i < length; i++) {
        void* player = items[i];
        if (!player) continue;

        Entity ent;
        ent.ptr = player;

        // Read with safety
        ent.pos = SafeRead<Vector3>( (Vector3*)((uintptr_t)player + ShowEntity__Position) );
        ent.hp = SafeRead<float>( (float*)((uintptr_t)player + EntityBase_m_Hp), 0.0f );
        ent.hpMax = SafeRead<float>( (float*)((uintptr_t)player + EntityBase_m_HpMax), 100.0f );
        ent.isDead = SafeRead<bool>( (bool*)((uintptr_t)player + EntityBase_m_bDeath), true );
        bool sameCamp = SafeRead<bool>( (bool*)((uintptr_t)player + EntityBase_m_bSameCampType), true );
        ent.isEnemy = !sameCamp;
        ent.level = SafeRead<int>( (int*)((uintptr_t)player + EntityBase_m_Level), 0 );
        ent.id = SafeRead<uint32_t>( (uint32_t*)((uintptr_t)player + EntityBase_m_ID), 0 );
        ent.name = (char*)player + ShowEntity_m_RoleName; // can't safely read string

        if (player == localPlayerPtr || ent.isDead) continue;
        entities.push_back(ent);
    }

    printf("[ESP] Found %zu entities\n", entities.size());
    pthread_mutex_unlock(&entityMutex);
}

// ===== Draw ESP (same as before, but with sanity)
void DrawESP() {
    if (!espEnabled) return;

    void* cam = cameraPtr;
    if (!cam) {
        cam = (void*)Camera_get_main;  // hardcoded pointer — verify this offset!
        if (!cam) {
            printf("[ESP] Camera is null\n");
            return;
        }
        cameraPtr = cam;
    }

    float screenW = GetScreenWidth();
    float screenH = GetScreenHeight();
    if (screenW <= 0 || screenH <= 0) return;

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
        snprintf(label, sizeof(label), "%s [%.0fm]", name, dist * 0.3f);
        DrawText(label, screenPos.x, top - 16, 1.0f, 1.0f, 1.0f, 1.0f);
    }
    pthread_mutex_unlock(&entityMutex);
}

// ===== Hook
void* HookedUpdate(void* battleManager) {
    if (!battleManager) return nullptr;

    void* (*originalUpdate)(void*) = (void* (*)(void*))BattleManager_Update;
    if (!originalUpdate) return nullptr;

    void* result = originalUpdate(battleManager);

    UpdateEntities();
    DrawESP();

    return result;
}

extern "C" void mlbb_esp_init() {
    printf("[ESP] Injected. ESP is active.\n");
}
