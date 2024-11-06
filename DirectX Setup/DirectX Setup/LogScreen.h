#pragma once
#include "AUIScreen.h"
class LogScreen : public AUIScreen {
public:
	LogScreen(String name);
	virtual ~LogScreen();
	virtual void DrawUI() override;
};

