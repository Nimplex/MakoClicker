#ifndef GUI_H
#define GUI_H

#include "imgui.h"

class GUI {
private:
    static constexpr auto GREEN = ImVec4(0.0f, 0.8f, 0.4f, 1.0f);
    static constexpr auto RED = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
    static constexpr auto ORANGE = ImVec4(1.0f, 0.6f, 0.0f, 1.0f);
    static constexpr float LABEL_WIDTH = 200.0f;

    static void drawLabeledSlider(const char *label, const char *sliderID, int *value, int min, int max) {
        ImGui::AlignTextToFramePadding();
        ImGui::Text("%s", label);
        ImGui::SameLine(LABEL_WIDTH);
        ImGui::SetNextItemWidth(150);
        ImGui::SliderInt(sliderID, value, min, max);
    }

    static void drawShortcutControl(const char *label, KeyCombination &shortcut, bool &pressed, bool &isRecording,
                                    const char *buttonID) {
        ImGui::AlignTextToFramePadding();
        ImGui::Text("%s", label);
        ImGui::SameLine(LABEL_WIDTH);

        if (isRecording) {
            ImGui::TextColored(ORANGE, "Recording... Press any key combination");

            const KeyCombination newCombo = InputHandler::recordKeyPress();
            if (!newCombo.isEmpty()) {
                shortcut = newCombo;
                pressed = true;
                isRecording = false;
            }

            ImGui::Spacing();
            if (ImGui::Button("Cancel")) {
                isRecording = false;
            }
        } else {
            ImGui::TextDisabled("%s", shortcut.toString().c_str());
            ImGui::SameLine();
            if (ImGui::Button(buttonID)) {
                isRecording = true;
            }
        }
    }

public:
    static void renderStatusSection(const State &state) {
        ImGui::Text("Autoclicker status:");

        ImGui::Text("- Mouse: ");
        ImGui::SameLine(0, 0);
        ImGui::TextColored(state.mouse.enabled ? GREEN : RED, state.mouse.enabled ? "ON" : "OFF");

        ImGui::Text("- Keyboard: ");
        ImGui::SameLine(0, 0);
        ImGui::TextColored(state.keyboard.enabled ? GREEN : RED, state.keyboard.enabled ? "ON" : "OFF");

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();
    }

    static void renderMouseSettings(State &state) {
        ImGui::Spacing();

        if (ImGui::CollapsingHeader("Mouse Settings", ImGuiTreeNodeFlags_None)) {
            ImGui::Spacing();

            drawLabeledSlider("Mouse delay (ms)", "##MouseDelay", &state.mouse.delay, 1, 2000);

            ImGui::Spacing();

            drawShortcutControl("Shortcut:", state.mouse.shortcut, state.mouse.pressed, state.recordingMouseShortcut,
                                "Record##Mouse");

            ImGui::Spacing();
        }
    }

    static void renderKeyboardSettings(State &state) {
        ImGui::Spacing();

        if (ImGui::CollapsingHeader("Keyboard Settings", ImGuiTreeNodeFlags_None)) {
            ImGui::Spacing();

            drawLabeledSlider("Keyboard delay (ms)", "##KeyboardDelay", &state.keyboard.delay, 1, 2000);

            ImGui::Spacing();

            ImGui::AlignTextToFramePadding();
            ImGui::Text("Target key:");
            ImGui::SameLine(LABEL_WIDTH);

            static int selectedTargetKey = 0;
            const auto TARGET_KEYS = KeyUtils::getAllKeys();

            for (int i = 0; i < TARGET_KEYS.size(); ++i) {
                if (TARGET_KEYS[i].vkCode == state.keyboard.targetKey) {
                    selectedTargetKey = i;
                    break;
                }
            }

            ImGui::SetNextItemWidth(150);
            if (ImGui::BeginCombo("##TargetKey", TARGET_KEYS[selectedTargetKey].displayName)) {
                for (int i = 0; i < TARGET_KEYS.size(); ++i) {
                    const bool isSelected = (selectedTargetKey == i);
                    if (ImGui::Selectable(TARGET_KEYS[i].displayName, isSelected)) {
                        selectedTargetKey = i;
                        state.keyboard.targetKey = TARGET_KEYS[i].vkCode;
                    }

                    if (isSelected) {
                        ImGui::SetItemDefaultFocus();
                    }
                }
                ImGui::EndCombo();
            }

            ImGui::Spacing();

            drawShortcutControl("Shortcut:", state.keyboard.shortcut, state.keyboard.pressed,
                                state.recordingKeyboardShortcut, "Record##Keyboard");

            ImGui::Spacing();
        }
    }

    static void renderControlButtons(State &state, bool &running) {
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        if (ImGui::Button("Stop All")) {
            state.mouse.enabled = false;
            state.keyboard.enabled = false;
            state.stopAllRecording();
        }

        ImGui::SameLine();

        if (ImGui::Button("Exit")) {
            running = false;
        }
    }

    static void render(State &state, bool &running, const int width, const int height) {
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(static_cast<float>(width), static_cast<float>(height)));

        ImGui::Begin("Mako GUI", nullptr,
                     ImGuiWindowFlags_NoTitleBar |
                     ImGuiWindowFlags_NoSavedSettings |
                     ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_NoMove |
                     ImGuiWindowFlags_NoCollapse);

        renderStatusSection(state);
        renderMouseSettings(state);
        renderKeyboardSettings(state);
        renderControlButtons(state, running);

        ImGui::End();
    }
};

#endif // GUI_H
