#pragma once
#include "AUIScreen.h"
class ColorPicker : public AUIScreen {
public:
	ColorPicker(String name);
	virtual ~ColorPicker();
	virtual void DrawUI() override;
};

