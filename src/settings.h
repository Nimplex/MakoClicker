//
// Created by Pszemek on 8.06.2025.
//

#ifndef SETTINGS_H
#define SETTINGS_H

#include "keys.h"
#include "chrono"

struct MouseSettings {
    int delay = 100;
    KeyCombination shortcut = {VK_F1, false, false, false};
    bool enabled = false;
    bool pressed = false;
    std::chrono::steady_clock::time_point lastClick;
};

struct KeyboardSettings {
    int delay = 50;
    KeyCombination shortcut = {VK_F2, false, false, false};
    int targetKey = VK_SPACE;
    bool enabled = false;
    bool pressed = false;
    std::chrono::steady_clock::time_point lastPress;
};

struct State {
    MouseSettings mouse;
    KeyboardSettings keyboard;

    bool recordingMouseShortcut = false;
    bool recordingKeyboardShortcut = false;

    void stopAllRecording() {
        recordingMouseShortcut = false;
        recordingKeyboardShortcut = false;
    }
};

#endif //SETTINGS_H
