#include "DetailsScreen.h"

DetailsScreen::DetailsScreen(String name) : AUIScreen(name) {

}

DetailsScreen::~DetailsScreen() {

}

void DetailsScreen::DrawUI() {
    ImGui::Begin("Details");

    ImGui::Text("Transform");
    ImGui::Text("Script_1");
    ImGui::Text("Rigidbody3D");
    ImGui::Text("Materials");
    ImGui::Text("AudioPlayer");
    ImGui::Text("SphereCollider");
    ImGui::Text("Script_2");
    ImGui::Text("Light");
    ImGui::Text("Script_3");
    ImGui::Text("Script_4");

    ImGui::End();
}
