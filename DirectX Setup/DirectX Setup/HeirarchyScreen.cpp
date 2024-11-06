#include "HeirarchyScreen.h"

HeirarchyScreen::HeirarchyScreen(String name) : AUIScreen(name) {

}

HeirarchyScreen::~HeirarchyScreen() {

}

void HeirarchyScreen::DrawUI() {
    ImGui::Begin("Scene 1");

    ImGui::Text("Directional Light");
    ImGui::Text("Cube");
    ImGui::Text("Quad");
    ImGui::Text("Main Camera");
    ImGui::Text("Event System");

    ImGui::End();
}
