#include "MenuScreen.h"
#include "UIManager.h"

MenuScreen::MenuScreen(String name) : AUIScreen(name) {

}

MenuScreen::~MenuScreen() {

}

void MenuScreen::DrawUI() {
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, 30));

    ImGuiWindowFlags toolbarFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings;

    ImGui::Begin("Toolbar", nullptr, toolbarFlags);

    ImGui::Text("MyScene");
    ImGui::SameLine();

    if (ImGui::Button("Scenes")) {
        ImGui::OpenPopup("AboutMenu");
    }

    if (ImGui::BeginPopup("AboutMenu")) {
        if (ImGui::MenuItem("Scene 1")) {
            UIManager::GetInstance()->SpawnScene();
        }
        ImGui::EndPopup();
    }
    ImGui::SameLine();
    UIManager::GetInstance()->MainDockWindow();

    ImGui::End();
}
