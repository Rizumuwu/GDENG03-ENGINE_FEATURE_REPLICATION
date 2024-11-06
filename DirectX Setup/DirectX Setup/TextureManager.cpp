
#include <d3d11.h>
#include <wrl.h>
#include <stdexcept>
#include "TextureManager.h"
#include "GraphicsEngine.h"
#include "WICTextureLoader11.h"

using namespace Microsoft::WRL;
using namespace DirectX;

ID3D11ShaderResourceView* TextureManager::LoadTexture(const std::string& filePath) {
    ID3D11ShaderResourceView* textureView = nullptr;

    // Load the texture using DirectX
    HRESULT result = DirectX::CreateWICTextureFromFile(
        GraphicsEngine::get()->GetRenderSystem()->GetDevice(),
        std::wstring(filePath.begin(), filePath.end()).c_str(),
        nullptr,
        &textureView
    );

    if (FAILED(result)) {
        throw std::runtime_error("Failed to load texture: " + filePath);
    }

    return textureView;
}

void TextureManager::UnloadTexture(ID3D11ShaderResourceView* texture) {
    if (texture) {
        texture->Release();
    }
}