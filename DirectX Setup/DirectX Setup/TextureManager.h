#pragma once

#include <d3d11.h>
#include <wrl/client.h>
#include <string>

class TextureManager {
public:
    static ID3D11ShaderResourceView* LoadTexture(const std::string& filePath);
    static void UnloadTexture(ID3D11ShaderResourceView* texture);
};