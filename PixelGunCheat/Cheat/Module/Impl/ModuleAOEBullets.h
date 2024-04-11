﻿#pragma once
#include "../ModuleBase.h"

const static BKCModule __aoe_bullets = { "AOE Bullets", COMBAT, 0x0, false, {}, {} };

class ModuleAOEBullets : ModuleBase
{
public:
    ModuleAOEBullets() : ModuleBase(__aoe_bullets) {}
    
    void do_module(void* arg) override
    {
        set_bool(arg, 0x3C0, true); // isSectorsAOE
        set_bool(arg, 0x34C, false); // flamethrower
        set_bool(arg, 0x1B4, false); // railgun
        set_bool(arg, 0x12B, false); // bazooka
        set_bool(arg, 0x2B8, false); // harpoon
        set_float(arg, 0x3C8, 360); // sectorsAOEAngleBack
        set_float(arg, 0x3C4, 360); // sectorsAOEAngleFront
        set_float(arg, 0x3D4, 5); // sectorsAOEDamageMultiplierBack
        set_float(arg, 0x3CC, 5); // sectorsAOEDamageMultiplierFront
        set_float(arg, 0x3D0, 5); // sectorsAOEDamageMultiplierSide
        set_float(arg, 0x3D8, 99999); // sectorsAOERadiusSectorsAoE
    }
};
