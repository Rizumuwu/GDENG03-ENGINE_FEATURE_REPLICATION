#include "UIManager.h"
#include "Prerequisites.h"
#include "GraphicsEngine.h"
#include "MenuScreen.h"
#include "ColorPicker.h"
#include "CreditsScreen.h"

UIManager* UIManager::sharedInstance = NULL;

UIManager* UIManager::GetInstance() {
	return sharedInstance;
}

void UIManager::Init(HWND windowHandle) {
	sharedInstance = new UIManager(windowHandle);
}

void UIManager::Destroy() {
	delete sharedInstance;
}

void UIManager::DrawAllUI() {
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	for (int i = 0; i < this->uiList.size(); i++) {
		this->uiList[i]->DrawUI();
	}

	ImGui::Render();
	//GraphicsEngine::get()->GetRenderSystem()->GetContext()->OMSetRenderTargets(1, &this->m_swap_chain->m_rtv, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void UIManager::SpawnColorPicker() {
	UINames uiNames;
	ColorPicker* colorPicker = new ColorPicker("ColorPicker_1");
	this->uiTable[uiNames.COLORPICKER_SCREEN] = colorPicker;
	this->uiList.push_back(colorPicker);
}

void UIManager::SpawnCredits() {
	UINames uiNames;
	CreditsScreen* creditsScreen = new CreditsScreen("Credits_1");
	this->uiTable[uiNames.CREDITS_SCREEN] = creditsScreen;
	this->uiList.push_back(creditsScreen);
}


void UIManager::MainDockWindow()
{
	ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	ImGuiViewport* viewport = ImGui::GetMainViewport();

	ImGui::SetNextWindowPos(viewport->WorkPos);
	ImGui::SetNextWindowSize(viewport->WorkSize);
	ImGui::SetNextWindowViewport(viewport->ID);

	// Additional flags to remove title bar, resize, move, and so on
	windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

	ImGui::Begin("Main DockSpace", nullptr, windowFlags);
	ImGui::PopStyleVar(2);

	// Create a dock space
	ImGuiID dockspace_id = ImGui::GetID("MainDockSpace");
	ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);
	ImGui::End();
}


UIManager::UIManager(HWND windowHandle) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	//io.ConfigFlags != ImGuiConfigFlags_NavEnableKeyboard;	// keyboard controls
	//io.ConfigFlags != ImGuiConfigFlags_NavEnableGamepad;	// Gamepad controls

	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(windowHandle);
	ImGui_ImplDX11_Init(GraphicsEngine::get()->GetRenderSystem()->GetDevice(), GraphicsEngine::get()->GetRenderSystem()->GetContext());

	UINames uiNames;
	MenuScreen* menuScreen = new MenuScreen("Menu_1");
	this->uiTable[uiNames.MENU_SCREEN] = menuScreen;
	this->uiList.push_back(menuScreen);
}

UIManager::~UIManager() {

}
