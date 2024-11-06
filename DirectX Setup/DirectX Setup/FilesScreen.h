#pragma once
#include "AUIScreen.h"
class FilesScreen : public AUIScreen {
public:
	FilesScreen(String name);
	virtual ~FilesScreen();
	virtual void DrawUI() override;
};
