#pragma once
#include "AUIScreen.h"
class AnimScreen : public AUIScreen {
public:
	AnimScreen(String name);
	virtual ~AnimScreen();
	virtual void DrawUI() override;
};

