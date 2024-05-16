﻿#pragma once
#include <imgui.h>

#include "../../ModuleBase.h"
#include "../../../Hooks/Hooks.h"
#include "../../../Internal/Functions.h"

static BKCDropdown __module_sort_type = BKCDropdown("Module Sort", L"Text Length", { L"Alphabetic", L"Text Length" });
static BKCDropdown __screen_position = BKCDropdown("Position", L"Top Left", { L"Top Left", L"Top Right" });
static BKCSliderInt __background_opacity = BKCSliderInt("Background Opacity (%)", 50, 0, 100, "Changes how dark the background renders as");
static BKCSliderInt __module_separation = BKCSliderInt("Y Separation", 1, 0, 12, "Distance on the vertical axis between modules");
static BKCCheckbox __line_on_side = BKCCheckbox("Line on Side", true, "Adds a line to the side of every module");
static BKCCheckbox __dont_extend_bg_on_separation = BKCCheckbox("No Extend Background", false, "Disables background extending on module separation");
static BKCModule __array_list = { "Module List", "Shows your enabled modules", VISUAL, 0x0, true, { &__module_sort_type, &__screen_position, &__background_opacity, &__module_separation, &__line_on_side, &__dont_extend_bg_on_separation } };

static ImU32 color_array = ImGui::ColorConvertFloat4ToU32(Functions::ImVec4i(255, 180, 230));

class ModuleArrayList : ModuleBase
{
public:
    ModuleArrayList() : ModuleBase(&__array_list) {}
    
    void do_module(void* arg) override
    {
        ImGui::PushFont(BKCImGuiHooker::arraylist_font);
        
        // ArrayList
        const int win_width = ClientUtil::win_size_info.right - ClientUtil::win_size_info.left;
        const float win_width_float = (float)win_width;
        const float bg_offset = 4;
        const float extra_offset = __line_on_side.enabled ? 2 : 0;
        float x = 0;
        float y = 0;

        // std::cout << win_width << std::endl;
        // std::cout << win_width_float << std::endl;
        
        switch (__screen_position.current_index)
        {
        case 0:
            x = 5;
            y = 48 * BKCImGuiHooker::scale_factor;
            break;
        case 1:
            y = 5 * BKCImGuiHooker::scale_factor;
            break;
        default:
            Logger::log_err("Unhandled __screen_position index!");
        }
        
        float size = ImGui::GetFontSize();
        float modc = 0;

        std::vector<BKCModule*> module_list = {};
        for (const auto mod : BKCImGuiHooker::modules)
        {
            if (mod->enabled)
            {
                module_list.push_back(mod);
                modc++;
            }
        }

        std::ranges::sort(module_list, mod_list_cmp());
        
        for (auto& mod : module_list)
        {
            float mod_y = (float)__module_separation.value;

            if (__dont_extend_bg_on_separation.enabled)
            {
                mod_y = 0;
            }

            ImVec2 text_size = ImGui::CalcTextSize(mod->name.c_str());
            
            if (__background_opacity.value != 0)
            {
                if (__screen_position.current_index == 1)
                {
                    x = win_width_float - (7 + text_size.x * BKCImGuiHooker::scale_factor);
                    ImGui::GetBackgroundDrawList()->AddRectFilled({ x - bg_offset * 2 - extra_offset, y + 2 }, { x + text_size.x * BKCImGuiHooker::scale_factor, y + text_size.y + mod_y + 2 }, ImGui::ColorConvertFloat4ToU32({ 0.00f, 0.00f, 0.00f, (float)__background_opacity.value / 100.0f }), 0);
                    ImGui::GetBackgroundDrawList()->AddRectFilled({ win_width_float - 7 - extra_offset, y + 2 }, { win_width_float - 7, y + text_size.y + mod_y + 2 }, color_array, 0);
                }
                else
                {
                    ImGui::GetBackgroundDrawList()->AddRectFilled({ x, y + 2 }, { x + text_size.x * BKCImGuiHooker::scale_factor + bg_offset * 2 + extra_offset, y + text_size.y + mod_y + 2 }, ImGui::ColorConvertFloat4ToU32({ 0.00f, 0.00f, 0.00f, (float)__background_opacity.value / 100.0f }), 0);
                    ImGui::GetBackgroundDrawList()->AddRectFilled({ x, y + 2 }, { x + extra_offset, y + text_size.y + mod_y + 2 }, color_array, 0);
                }
            }
            
            switch (__screen_position.current_index)
            {
            case 0:
                ImGui::GetBackgroundDrawList()->AddText(nullptr, size, { x + 1 + bg_offset + extra_offset, y + 2 + mod_y / 2 + 1 }, ImGui::ColorConvertFloat4ToU32({ 0.0f, 0.0f, 0.0f, 1.0f }), mod->name.c_str());
                ImGui::GetBackgroundDrawList()->AddText(nullptr, size, { x + bg_offset + extra_offset, y + 2 + mod_y / 2 }, color_array, mod->name.c_str());
                break;
            case 1:
            {
                ImGui::GetBackgroundDrawList()->AddText(nullptr, size, { win_width_float - text_size.x - (6 + bg_offset + extra_offset), y + 2 + mod_y / 2 + 1 }, ImGui::ColorConvertFloat4ToU32({ 0.0f, 0.0f, 0.0f, 1.0f }), mod->name.c_str());
                ImGui::GetBackgroundDrawList()->AddText(nullptr, size, { win_width_float - text_size.x - (7 + bg_offset + extra_offset), y + 2 + mod_y / 2 }, color_array, mod->name.c_str());
                break;
            }
            default:
                Logger::log_err("Unhandled __screen_position index!");
            }
            
            y += size + (float)__module_separation.value;
        }
        
        ImGui::PopFont();
    }
private:
    struct mod_list_cmp
    {
        bool operator() (const BKCModule* mod1, const BKCModule* mod2) const
        {
            switch (__module_sort_type.current_index)
            {
            case 0:
                return mod1->name.compare(mod2->name) <= 0;
            case 1:
            {
                ImVec2 mod1_size = ImGui::CalcTextSize(mod1->name.c_str());
                ImVec2 mod2_size = ImGui::CalcTextSize(mod2->name.c_str());
                return mod1_size.x >= mod2_size.x;
            }
            default:
                return true;
            }
        }
    };
};
