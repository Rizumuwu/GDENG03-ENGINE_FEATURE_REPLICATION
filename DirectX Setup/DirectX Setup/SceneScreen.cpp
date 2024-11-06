#include "SceneScreen.h"
#include <stdexcept>

SceneScreen::SceneScreen(String name) : AUIScreen(name) {
    try {
        textureID = TextureManager::LoadTexture("sampleScene.png");
    }
    catch (const std::runtime_error& e) {

    }
}

SceneScreen::~SceneScreen() {
    TextureManager::UnloadTexture(textureID);
}

void SceneScreen::DrawUI() {
    ImGui::Begin("Scene");

    if (textureID != nullptr) {
        ImGui::Image(reinterpret_cast<ImTextureID>(textureID), ImVec2(200, 150));
    }
    else {
        ImGui::Text("Image not loaded.");
    }

    ImGui::End();
}
