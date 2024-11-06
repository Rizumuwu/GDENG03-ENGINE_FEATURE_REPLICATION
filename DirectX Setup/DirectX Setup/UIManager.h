#pragma once
#include "AUIScreen.h"
#include <vector>
#include <unordered_map>
#include <Windows.h>

class UINames {
public:
	const String MENU_SCREEN = "MENU_SCREEN";
	const String COLORPICKER_SCREEN = "COLORPICKER_SCREEN";
	const String CREDITS_SCREEN = "CREDITS_SCREEN";
};

class UIManager {
public:
	typedef std::string String;
	typedef std::vector<AUIScreen*> UIList;
	typedef std::unordered_map<String, AUIScreen*> UITable;

	static UIManager* GetInstance();
	static void Init(HWND windowHandle);
	static void Destroy();

	void DrawAllUI();
	void SpawnColorPicker();
	void SpawnCredits();
	void MainDockWindow();

	static const int WINDOW_HEIGHT = 1440;
	static const int WINDOW_WIDTH = 900;

private:
	UIManager(HWND windowHandle);
	~UIManager();
	UIManager(UIManager const&) {};
	UIManager& operator=(UIManager const&) {};
	static UIManager* sharedInstance;

	UIList uiList;
	UITable uiTable;
};