#pragma once
#include <stdint.h>
#define OBFUSCATE(x) x

// ===== ShowEntity (Base class for all entities)
#define EntityBase_m_dRunSpeed (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "ShowEntity", OBFUSCATE("m_dRunSpeed"))
#define EntityBase_m_ID (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "ShowEntity", OBFUSCATE("m_ID"))
#define Fields_ShowEntity_MoveDir (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "ShowEntity", "_MoveDir")
#define EntityBase_m_Level (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "ShowEntity", OBFUSCATE("m_Level"))
#define EntityBase_m_bDeath (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "ShowEntity", OBFUSCATE("m_bDeath"))
#define EntityBase_m_bSameCampType (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "ShowEntity", OBFUSCATE("m_bSameCampType"))
#define EntityBase_m_Hp (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "ShowEntity", OBFUSCATE("m_Hp"))
#define EntityBase_m_HpMax (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "ShowEntity", OBFUSCATE("m_HpMax"))
#define EntityBase_m_iSummonSkillId (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "ShowPlayer", OBFUSCATE("m_iSummonSkillId"))
#define EntityBase_m_EntityCampType (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "ShowEntity", OBFUSCATE("m_EntityCampType"))

// ===== ShowEntity positions
#define ShowEntity__Position (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("ShowEntity"), OBFUSCATE("m_vCachePosition"))
#define ShowEntity_MoveDir (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("ShowEntity"), OBFUSCATE("_MoveDir"))
#define ShowEntity_Position (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "ShowEntity", OBFUSCATE("<LastPosition>k__BackingField"))
#define ShowEntity_m_bShowLayer (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "ShowEntity", OBFUSCATE("m_bShowLayer"))
#define ShowEntity_bShowEntityLayer (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "ShowEntity", OBFUSCATE("bShowEntityLayer"))
#define ShowEntity_m_OwnSkillComp (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "ShowEntity", OBFUSCATE("m_OwnSkillComp"))
#define ShowEntity_m_RoleName (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "ShowEntity", OBFUSCATE("m_RoleName"))
#define ShowEntity__logicFighter (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "ShowEntity", "_logicFighter")

// ===== ShowEntity methods
#define ShowEntity_get_InTransformation (uintptr_t) Il2CppGetMethodOffset("Assembly-CSharp.dll", "", "ShowEntity", OBFUSCATE("get_InTransformation"))
#define ShowEntity_set_DesPosition (uintptr_t) Il2CppGetMethodOffset("Assembly-CSharp.dll", "", "ShowEntity", OBFUSCATE("set_DesPosition"), 1)
#define ShowEntity_set_Position (uintptr_t) Il2CppGetMethodOffset("Assembly-CSharp.dll", "", "ShowEntity", OBFUSCATE("set_Position"), 1)
#define ShowEntity_set_LastPosition (uintptr_t) Il2CppGetMethodOffset("Assembly-CSharp.dll", "", "ShowEntity", OBFUSCATE("set_LastPosition"), 1)

// ===== ShowPlayer (inherits from ShowEntity)
#define ShowPlayer_m_iOriginHeroId 0x8B8
#define ShowPlayer_m_HeroName (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "ShowPlayer", OBFUSCATE("m_HeroName"))

// ===== BattleManager
#define BattleManager_m_LocalPlayerShow (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "BattleManager", OBFUSCATE("m_LocalPlayerShow"))
#define BattleManager_m_dicPlayerShow (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "BattleManager", OBFUSCATE("m_dicPlayerShow"))
#define BattleManager_m_dicMonsterShow (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "BattleManager", OBFUSCATE("m_dicMonsterShow"))
#define BattleManager_m_ShowPlayers (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("BattleManager"), OBFUSCATE("m_ShowPlayers"))
#define BattleManager_m_ShowMonsters (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("BattleManager"), OBFUSCATE("m_ShowMonsters"))
#define BattleManager_Update (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE(""), OBFUSCATE("BattleManager"), OBFUSCATE("Update"))

// ===== LogicPlayer
#define LogicPlayer_m_KillWildTimes (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("Battle"), OBFUSCATE("LogicPlayer"), OBFUSCATE("_KillWildTimes"))

// ===== Camera
#define Camera_get_main (uintptr_t) Il2CppGetMethodOffset("UnityEngine.dll", "UnityEngine", "Camera", OBFUSCATE("get_main"))
#define Camera_WorldToScreenPoint (uintptr_t) Il2CppGetMethodOffset("UnityEngine.dll", "UnityEngine", "Camera", OBFUSCATE("WorldToScreenPoint"), 1)
#define Camera_get_fieldOfView (uintptr_t) Il2CppGetMethodOffset("UnityEngine.dll", "UnityEngine", "Camera", "get_fieldOfView")
#define Camera_set_fieldOfView (uintptr_t) Il2CppGetMethodOffset("UnityEngine.dll", "UnityEngine", "Camera", "set_fieldOfView", 1)

// ===== Transform
#define Transform_get_position (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Transform"), OBFUSCATE("get_position"))
#define Transform_get_localPosition (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Transform"), OBFUSCATE("get_localPosition"))

// ===== Screen
#define Screen_get_width (uintptr_t) Il2CppGetMethodOffset("UnityEngine.dll", "UnityEngine", "Screen", OBFUSCATE("get_width"))
#define Screen_get_height (uintptr_t) Il2CppGetMethodOffset("UnityEngine.dll", "UnityEngine", "Screen", OBFUSCATE("get_height"))
#define Screen_get_dpi (uintptr_t) Il2CppGetMethodOffset("UnityEngine.dll", "UnityEngine", "Screen", OBFUSCATE("get_dpi"))
#define Screen_SetResolution (uintptr_t) Il2CppGetMethodOffset("UnityEngine.dll", "UnityEngine", "Screen", OBFUSCATE("SetResolution"), 3)

// ===== Unity Array helpers
#define Array_length 0x08
#define Array_items 0x10
