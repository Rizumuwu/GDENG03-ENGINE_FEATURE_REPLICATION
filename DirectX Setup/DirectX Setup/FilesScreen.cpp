#include "FilesScreen.h"

FilesScreen::FilesScreen(String name) : AUIScreen(name) {

}

FilesScreen::~FilesScreen() {

}

void FilesScreen::DrawUI() {
    ImGui::Begin("Internal Files");

    ImGui::Text("Assets");
    ImGui::Text("Scenes");
    ImGui::Text("Materials");
    ImGui::Text("Prefabs");
    ImGui::Text("Audio");

    ImGui::End();
}
