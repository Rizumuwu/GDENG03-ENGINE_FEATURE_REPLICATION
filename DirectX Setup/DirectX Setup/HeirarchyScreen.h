#pragma once
#include "AUIScreen.h"
class HeirarchyScreen : public AUIScreen {
public:
	HeirarchyScreen(String name);
	virtual ~HeirarchyScreen();
	virtual void DrawUI() override;
};

