//
// Created by Pszemek on 8.06.2025.
//

#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "keys.h"
#include "settings.h"

class InputHandler {
public:
    static void checkShortcuts(State& state) {
        if (state.recordingKeyboardShortcut || state.recordingMouseShortcut) {
            return;
        }

        const bool keyboardPressed = state.keyboard.shortcut.isPressed();
        const bool mousePressed = state.mouse.shortcut.isPressed();
        const auto now = std::chrono::steady_clock::now();

        if (keyboardPressed && !state.keyboard.pressed) {
            state.keyboard.enabled = !state.keyboard.enabled;
            if (state.keyboard.enabled) {
                state.keyboard.lastPress = now;
            }
        }

        if (mousePressed && !state.mouse.pressed) {
            state.mouse.enabled = !state.mouse.enabled;
            if (state.mouse.enabled) {
                state.mouse.lastClick = now;
            }
        }

        state.keyboard.pressed = keyboardPressed;
        state.mouse.pressed = mousePressed;
    }

    static KeyCombination recordKeyPress() {
        KeyCombination combo;

        combo.ctrl = (GetAsyncKeyState(VK_CONTROL) & 0x8000) != 0;
        combo.shift = (GetAsyncKeyState(VK_SHIFT) & 0x8000) != 0;
        combo.alt = (GetAsyncKeyState(VK_MENU) & 0x8000) != 0;

        for (const auto& key : KeyUtils::getAllKeys()) {
            if (GetAsyncKeyState(key.vkCode) & 0x8000) {
                if (!KeyUtils::isModifierKey(key.vkCode)) {
                    combo.vkCode = key.vkCode;
                    return combo;
                }
            }
        }

        return {};
    }

    static void performMouseClick() {
        INPUT input = {0};
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
        SendInput(1, &input, sizeof(INPUT));

        input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
        SendInput(1, &input, sizeof(INPUT));
    }

    static void performKeyboardClick(const int targetKey) {
        INPUT input = {0};
        input.type = INPUT_KEYBOARD;
        input.ki.wVk = targetKey;
        SendInput(1, &input, sizeof(INPUT));

        input.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &input, sizeof(INPUT));
    }

    static void processClicking(State& state) {
        const auto now = std::chrono::steady_clock::now();

        if (state.keyboard.enabled) {
            const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
                now - state.keyboard.lastPress).count();
            if (elapsed >= state.keyboard.delay) {
                performKeyboardClick(state.keyboard.targetKey);
                state.keyboard.lastPress = now;
            }
        }

        if (state.mouse.enabled) {
            const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
                now - state.mouse.lastClick).count();
            if (elapsed >= state.mouse.delay) {
                performMouseClick();
                state.mouse.lastClick = now;
            }
        }
    }
};

#endif //INPUT_HANDLER_H
