#include "MenuScreen.h"
#include "UIManager.h"

MenuScreen::MenuScreen(String name) : AUIScreen(name) {

}

MenuScreen::~MenuScreen() {

}

void MenuScreen::DrawUI() {
    // Set position and size for the toolbar
    ImGui::SetNextWindowPos(ImVec2(0, 0));  // Place at the top of the window
    ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, 40));  // Full width, fixed height

    // Set flags to make it a toolbar-style window
    ImGuiWindowFlags toolbarFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings;

    ImGui::Begin("Toolbar", nullptr, toolbarFlags);

    ImGui::Text("MyScene");
    ImGui::SameLine();

    if (ImGui::Button("About")) {
        ImGui::OpenPopup("AboutMenu");
    }

    // Create the dropdown menu
    if (ImGui::BeginPopup("AboutMenu")) {
        if (ImGui::MenuItem("Credits")) {
            UIManager::GetInstance()->SpawnCredits();
        }
        ImGui::EndPopup();
    }
    ImGui::SameLine();
    UIManager::GetInstance()->MainDockWindow();

    ImGui::End();
}
