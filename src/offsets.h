#pragma once
#include <stdint.h>

// ===== ShowEntity offsets (from SexDoggy.txt)
#define EntityBase_m_Hp 0x1A8
#define EntityBase_m_HpMax 0x1AC
#define EntityBase_m_bDeath 0x1B0
#define EntityBase_m_bSameCampType 0x1B4
#define EntityBase_m_Level 0x1B8
#define EntityBase_m_ID 0x1BC
#define EntityBase_m_EntityCampType 0x1C0

// ===== ShowEntity positions
#define ShowEntity__Position 0x1C4
#define ShowEntity_m_RoleName 0x1D0

// ===== ShowPlayer
#define ShowPlayer_m_iOriginHeroId 0x8B8

// ===== BattleManager
#define BattleManager_m_LocalPlayerShow 0x200
#define BattleManager_m_ShowPlayers 0x208
#define BattleManager_Update 0x210

// ===== Camera
#define Camera_get_main 0x1000          // placeholder - replace with actual offset
#define Camera_WorldToScreenPoint 0x1004 // placeholder - replace with actual offset

// ===== Screen
#define Screen_get_width 0x2000         // placeholder - replace with actual offset
#define Screen_get_height 0x2004        // placeholder - replace with actual offset

// ===== Unity Array helpers
#define Array_length 0x08
#define Array_items 0x10
