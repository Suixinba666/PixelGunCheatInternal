﻿#pragma once

#include <assert.h>
#include <cstdint>

#include "../Module/Impl/ModuleAOEBullets.h"

struct Ray
{
    float xo;
    float yo;
    float zo;
    float xd;
    float yd;
    float zd;
};

struct RaycastHit
{
    float px;
    float py;
    float pz;
    float nx;
    float ny;
    float nz;
    UINT face_id;
    float distance;
    float u;
    float v;
    int collider;
    
};

class Functions
{
public:
    static void init(uintptr_t game_base, uintptr_t game_assembly, uintptr_t unity_player);
    static void SetNextHitCritical(void* arg, bool arg1);
    static void MakeInvisibleForSeconds(void* arg, float duration);
    // static void AddHealthFromWeaponOnline(void* arg, float amount);
    // static void AddAmmoFromWeaponOnline(void* arg, float amount);
    static void* TextMeshGetText(void* arg);
    static void TextMeshGetColor(void* arg, void* color_ptr);
    static void CameraWorldToScreen(void* arg, void* world, void* screen);
    static void* ComponentGetTransform(void* arg);
    static void TransformGetRotation(void* arg, void* quaternion);
    static void TransformGetPosition(void* arg, void* position);
    static void TransformLookAt(void* arg, void* position, void* up);
    static bool PhysicsRaycast(void* ray, void* hit_info, float max_distance);
    static int ObjectGetInstanceID(void* arg);
    // static void* FindObjectsOfType(void* arg);
    // static void* FindObjectOfType(void* arg);
    static void* TypeGetType(void* arg);
    static bool BehaviourGetEnabled(void* arg);
    static void AddWeapon(void* arg, void* string, int source, bool bool1, bool bool2, void* class1, void* struct1);
    // static void* PlayerGetWeaponManager(void* arg);
    static void* GetItemRecordDict();
    static void* ItemRecordGetShopId(void* arg);
    // static void AddWearItem(int category, void* id);
    static void GiveWear(void* id);
    static void GiveWeapon(void* id, bool event, bool auto_upgrade);
    static void GivePets(void* id, int count);
    static void AddGems(int amount, bool arg1, bool arg2, int enum1, int enum2, int enum3);
    static void AddCoins(int amount, bool arg1, bool arg2, int enum1, int enum2, int enum3);
    static void AddCoupons(int amount, int source, bool arg1, int arg2);
    static void AddClanLootboxPoints(int amount, int source, bool arg1, bool arg2, int arg3);
    static void AddSomeCurrency(void* currency, int amount, bool arg1, int enum1, int enum2, int enum3, int enum4);
};
