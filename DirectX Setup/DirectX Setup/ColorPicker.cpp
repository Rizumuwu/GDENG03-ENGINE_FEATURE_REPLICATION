#include "ColorPicker.h"
#include "imgui_internal.h"
#include <cmath>

ColorPicker::ColorPicker(String name) : AUIScreen(name) {

}

ColorPicker::~ColorPicker() {

}

void ColorPicker::DrawUI() {
    ImGui::Begin("Color Picker");

    // Placeholder color variable (this would later be connected to functionality)
    static ImVec4 color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    ImGui::Text("Pick a color:");
    ImGui::ColorPicker4("Color", (float*)&color); // Basic color picker with RGBA sliders

    ImGui::End();
}
