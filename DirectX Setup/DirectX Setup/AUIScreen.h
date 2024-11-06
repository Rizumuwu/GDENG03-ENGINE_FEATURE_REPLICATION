#pragma once
#include <string>
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

typedef std::string String;
class UIManager;

class AUIScreen {
protected:
	typedef std::string String;

	AUIScreen(String name);
	~AUIScreen();

	String GetName();
	virtual void DrawUI() = 0;

	String name;

	friend class UIManager;
};

