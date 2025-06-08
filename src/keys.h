//
// Created by Pszemek on 8.06.2025.
//

#ifndef KEYS_H
#define KEYS_H

#include <Windows.h>
#include <string>
#include <vector>
#include <algorithm>

struct KeyInfo {
    int vkCode;
    const char *name;
    const char *displayName;
};

namespace KeyUtils {
    inline const std::vector<KeyInfo>& getAllKeys() {
        static const std::vector<KeyInfo> allKeys = {
            // Function keys
            {VK_F1, "F1", "F1"},    {VK_F2, "F2", "F2"},    {VK_F3, "F3", "F3"},
            {VK_F4, "F4", "F4"},    {VK_F5, "F5", "F5"},    {VK_F6, "F6", "F6"},
            {VK_F7, "F7", "F7"},    {VK_F8, "F8", "F8"},    {VK_F9, "F9", "F9"},
            {VK_F10, "F10", "F10"}, {VK_F11, "F11", "F11"}, {VK_F12, "F12", "F12"},

            // Navigation and control
            {VK_SPACE, "VK_SPACE", "Space"},    {VK_RETURN, "VK_RETURN", "Enter"},
            {VK_TAB, "VK_TAB", "Tab"},          {VK_BACK, "VK_BACK", "Backspace"},
            {VK_DELETE, "VK_DELETE", "Delete"}, {VK_INSERT, "VK_INSERT", "Insert"},
            {VK_HOME, "VK_HOME", "Home"},       {VK_END, "VK_END", "End"},
            {VK_PRIOR, "VK_PRIOR", "Page Up"},  {VK_NEXT, "VK_NEXT", "Page Down"},
            {VK_UP, "VK_UP", "Up Arrow"},       {VK_DOWN, "VK_DOWN", "Down Arrow"},
            {VK_LEFT, "VK_LEFT", "Left Arrow"}, {VK_RIGHT, "VK_RIGHT", "Right Arrow"},
            {VK_ESCAPE, "VK_ESCAPE", "Escape"},

            // Alphanumeric
            {'A', "A", "A"}, {'B', "B", "B"}, {'C', "C", "C"}, {'D', "D", "D"},
            {'E', "E", "E"}, {'F', "F", "F"}, {'G', "G", "G"}, {'H', "H", "H"},
            {'I', "I", "I"}, {'J', "J", "J"}, {'K', "K", "K"}, {'L', "L", "L"},
            {'M', "M", "M"}, {'N', "N", "N"}, {'O', "O", "O"}, {'P', "P", "P"},
            {'Q', "Q", "Q"}, {'R', "R", "R"}, {'S', "S", "S"}, {'T', "T", "T"},
            {'U', "U", "U"}, {'V', "V", "V"}, {'W', "W", "W"}, {'X', "X", "X"},
            {'Y', "Y", "Y"}, {'Z', "Z", "Z"}, {'0', "0", "0"}, {'1', "1", "1"},
            {'2', "2", "2"}, {'3', "3", "3"}, {'4', "4", "4"}, {'5', "5", "5"},
            {'6', "6", "6"}, {'7', "7", "7"}, {'8', "8", "8"}, {'9', "9", "9"}
        };
        return allKeys;
    }

    inline const char *getKeyDisplayName(int vkCode) {
        const std::vector<KeyInfo>& keys = getAllKeys();
        const auto it = std::find_if(keys.begin(), keys.end(), [vkCode](const KeyInfo &key) {
            return key.vkCode == vkCode;
        });
        return (it != keys.end()) ? it->displayName : "Unknown";
    }

    inline bool isModifierKey(const int vkCode) {
        return vkCode == VK_CONTROL || vkCode == VK_SHIFT || vkCode == VK_MENU;
    }

    inline bool isValidKey(int vkCode) {
        const auto& keys = getAllKeys();
        return std::any_of(keys.begin(), keys.end(), [vkCode](const KeyInfo &key) {
            return key.vkCode == vkCode;
        });
    }
}

struct KeyCombination {
    int vkCode = 0;
    bool ctrl = false;
    bool shift = false;
    bool alt = false;

    std::string toString() const {
        std::string result;
        if (ctrl) result += "Ctrl+";
        if (shift) result += "Shift+";
        if (alt) result += "Alt+";
        result += KeyUtils::getKeyDisplayName(vkCode);
        return result;
    }

    bool isEmpty() const {
        return vkCode == 0;
    }

    bool isPressed() const {
        const bool ctrlPressed  = !ctrl || (GetAsyncKeyState(VK_CONTROL) & 0x8000);
        const bool shiftPressed = !shift || (GetAsyncKeyState(VK_SHIFT) & 0x8000);
        const bool altPressed   = !alt || (GetAsyncKeyState(VK_MENU) & 0x8000);
        const bool keyPressed   = GetAsyncKeyState(vkCode) & 0x8000;

        return ctrlPressed && shiftPressed && altPressed && keyPressed;
    }
};

#endif //KEYS_H
