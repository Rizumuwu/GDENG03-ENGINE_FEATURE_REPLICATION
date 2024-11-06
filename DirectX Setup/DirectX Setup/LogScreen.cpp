#include "LogScreen.h"

LogScreen::LogScreen(String name) : AUIScreen(name) {

}

LogScreen::~LogScreen() {

}

void LogScreen::DrawUI() {
    ImGui::Begin("Output");

    ImGui::Text("WARNING: Variable_1 is uninitilaized. Always initialize class variables.");
    ImGui::Text("WARNING: Unreachable code detected.");
    ImGui::Text("ERROR: Unexpected token found in line 32. Expected '}'");

    ImGui::End();
}
