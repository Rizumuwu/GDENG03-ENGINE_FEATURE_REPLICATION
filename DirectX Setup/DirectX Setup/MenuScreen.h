#pragma once
#include "AUIScreen.h"

class MenuScreen : public AUIScreen {
public:
	MenuScreen(String name);
	virtual ~MenuScreen();
	virtual void DrawUI() override;
};

