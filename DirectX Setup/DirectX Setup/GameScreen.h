#pragma once
#include "AUIScreen.h"
#include <d3d11.h>
#include "TextureManager.h"

class GameScreen : public AUIScreen {
public:
	GameScreen(String name);
	virtual ~GameScreen();
	virtual void DrawUI() override;

private:
	ID3D11ShaderResourceView* textureID2;
};

