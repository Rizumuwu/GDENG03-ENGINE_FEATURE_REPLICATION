#pragma once
#include "AUIScreen.h"
#include <d3d11.h>
#include "TextureManager.h"

class CreditsScreen : public AUIScreen {
public:
	CreditsScreen(String name);
	virtual ~CreditsScreen();
	virtual void DrawUI() override;

private:
	ID3D11ShaderResourceView* textureID; // Change to use DirectX texture type
};

