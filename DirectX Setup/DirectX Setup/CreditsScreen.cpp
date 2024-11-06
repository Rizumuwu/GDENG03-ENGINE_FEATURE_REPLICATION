#include "CreditsScreen.h"
#include <stdexcept>

CreditsScreen::CreditsScreen(String name) : AUIScreen(name) {
    try {
        textureID = TextureManager::LoadTexture("DLSU_LOGO.png"); // Replace with your image path
    }
    catch (const std::runtime_error& e) {
        // Handle texture loading error (e.g., log it)
    }
}

CreditsScreen::~CreditsScreen() {
    TextureManager::UnloadTexture(textureID); // Unload texture in destructor
}

void CreditsScreen::DrawUI() {
    ImGui::Begin("Credits");

    // Check if the texture ID is valid
    if (textureID != nullptr) {
        // Display the image using ImGui::Image
        ImGui::Image(reinterpret_cast<ImTextureID>(textureID), ImVec2(200, 150));
    }
    else {
        ImGui::Text("Image not loaded.");
    }

    ImGui::Text("About\n\n\nScene Editor v0.0.0.2");
    ImGui::Text("Developed by: Miguel Gino V. Paglinawan");
    ImGui::Text("\nAcknowledgements:");
    ImGui::Text("PardCode Game Engine Tutorial");
    ImGui::Text("Doc. Neil's GDENG03 Course");

    ImGui::End();
}
