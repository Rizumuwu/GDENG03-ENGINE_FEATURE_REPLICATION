#pragma once
#include "AUIScreen.h"
class DetailsScreen : public AUIScreen {
public:
	DetailsScreen(String name);
	virtual ~DetailsScreen();
	virtual void DrawUI() override;
};

