#include "GameScreen.h"
#include <stdexcept>
#include <iostream>

GameScreen::GameScreen(String name) : AUIScreen(name) {
    try {
        textureID2 = TextureManager::LoadTexture("DLSU_LOGO.png");
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Failed to load texture: " << e.what() << std::endl;
    }
}

GameScreen::~GameScreen() {
    TextureManager::UnloadTexture(textureID2);
}

void GameScreen::DrawUI() {
    ImGui::Begin("Credits");

    if (textureID2 != nullptr) {
        ImGui::Image(reinterpret_cast<ImTextureID>(textureID2), ImVec2(200, 150));
    }
    else {
        ImGui::Text("Image not loaded.");
    }

    ImGui::Text("About\n\n\nScene Layouting");
    ImGui::Text("Developed by: Group 5");
    ImGui::Text("\nAcknowledgements:");
    ImGui::Text("PardCode Game Engine Tutorial");
    ImGui::Text("Doc. Neil's GDENG03 Course");

    ImGui::End();
}
