#include "SwapChain.h"
#include <iostream>
#include "RenderSystem.h"
#include <exception>

SwapChain::SwapChain(HWND hwnd, UINT width, UINT height, RenderSystem* system) : m_system(system) {
	this->m_system = system;

	ID3D11Device* device = m_system->m_d3d_device;

	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.BufferCount = 1;
	desc.BufferDesc.Width = width;
	desc.BufferDesc.Height = height;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = hwnd;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Windowed = TRUE;

	HRESULT hr = m_system->m_dxgi_factory->CreateSwapChain(device, &desc, &m_swap_chain);

	if (FAILED(hr))
	{
		//std::cout << "failed swap chain creation\n";
		throw std::exception("swap chain failed");
	}

	ID3D11Texture2D* buffer = NULL;
	hr = m_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);

	if (FAILED(hr))
	{
		//std::cout << "failed get buffer\n";
		throw std::exception(" swap chain failed to get buffer");
	}

	hr = device->CreateRenderTargetView(buffer, NULL, &m_rtv);
	buffer->Release();

	if (FAILED(hr))
	{
		//std::cout << "failed create rtv \n";
		throw std::exception("swap chain failed to make rtv");
	}

	D3D11_TEXTURE2D_DESC textDesc = {};
	textDesc.Width = width;
	textDesc.Height = height;
	textDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	textDesc.Usage = D3D11_USAGE_DEFAULT;
	textDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	textDesc.MipLevels = 1;
	textDesc.SampleDesc.Count = 1;
	textDesc.SampleDesc.Quality = 0;
	textDesc.MiscFlags = 0;
	textDesc.ArraySize = 1;
	textDesc.CPUAccessFlags = 0;

	HRESULT depthResult = device->CreateTexture2D(&textDesc, NULL, &buffer);
	HRESULT depthStencilResult = device->CreateDepthStencilView(buffer, NULL, &m_dsv);
	buffer->Release();
}

bool SwapChain::present(bool vsync) {
	m_swap_chain->Present(vsync, NULL);
	return true;
}

SwapChain::~SwapChain() {
	m_swap_chain->Release();
}
