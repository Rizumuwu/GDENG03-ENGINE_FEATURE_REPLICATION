#pragma once
#include "AUIScreen.h"
#include <d3d11.h>
#include "TextureManager.h"

class SceneScreen : public AUIScreen {
public:
	SceneScreen(String name);
	virtual ~SceneScreen();
	virtual void DrawUI() override;

private:
	ID3D11ShaderResourceView* textureID;
};

