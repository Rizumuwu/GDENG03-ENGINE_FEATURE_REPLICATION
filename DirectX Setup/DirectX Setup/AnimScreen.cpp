#include "AnimScreen.h"

AnimScreen::AnimScreen(String name) : AUIScreen(name) {

}

AnimScreen::~AnimScreen() {

}

void AnimScreen::DrawUI() {
    ImGui::Begin("Animation");

    ImGui::Text("This is the animation tab.");
    ImGui::Text("To get started, click on an object and press animate.");

    ImGui::End();
}
