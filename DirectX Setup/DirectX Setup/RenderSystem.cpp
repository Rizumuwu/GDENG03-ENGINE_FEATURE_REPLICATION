#include "RenderSystem.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"
#include <d3dcompiler.h>
#include "IndexBuffer.h"
#include <exception>

#pragma comment(lib, "D3DCompiler.lib")
#pragma comment(lib, "d3d11.lib")

RenderSystem::RenderSystem() {

}

bool RenderSystem::init() {

	D3D_DRIVER_TYPE driver_types[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};
	UINT num_driver_types = ARRAYSIZE(driver_types);

	D3D_FEATURE_LEVEL feature_levels[] =
	{
		D3D_FEATURE_LEVEL_11_0
	};
	UINT num_feature_levels = ARRAYSIZE(feature_levels);

	HRESULT res = 0;

	for (UINT driver_type_index = 0; driver_type_index < num_driver_types;)
	{
		res = D3D11CreateDevice(NULL, driver_types[driver_type_index], NULL, NULL, feature_levels,
			num_feature_levels, D3D11_SDK_VERSION, &m_d3d_device, &m_feature_level, &m_imm_context);

		if (SUCCEEDED(res))
			break;

		++driver_type_index;
	}

	if (FAILED(res))
		return false;

	m_imm_device_context = new DeviceContext(m_imm_context, this);

	m_d3d_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_dxgi_device);
	m_dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void**)&m_dxgi_adapter);
	m_dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_dxgi_factory);

	return true;
}

bool RenderSystem::release() {
	if (m_vs)m_vs->Release();
	if (m_ps)m_ps->Release();

	if (m_vsblob)m_vsblob->Release();
	if (m_psblob)m_psblob->Release();

	m_d3d_device->Release();
	m_dxgi_device->Release();
	m_dxgi_adapter->Release();

	delete m_imm_device_context;
	m_d3d_device->Release();
	return true;
}

SwapChain* RenderSystem::CreateSwapChain(HWND hwnd, UINT width, UINT height) {
	SwapChain* sc = nullptr;
	try {
		sc = new SwapChain(hwnd, width, height, this);
	}
	catch (...) {}
	
	return sc;
}

DeviceContext* RenderSystem::GetImmediateDeviceContext() {
	return this->m_imm_device_context;
}

ID3D11Device* RenderSystem::GetDevice()
{
	return this->m_d3d_device;
}

ID3D11DeviceContext* RenderSystem::GetContext()
{
	return this->m_imm_context;
}

VertexBuffer* RenderSystem::CreateVertexBuffer(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, size_t size_byte_shader) {
	VertexBuffer* vb = nullptr;
	try {
		vb = new VertexBuffer(list_vertices, size_vertex, size_list, shader_byte_code, size_byte_shader, this);
	}
	catch (...) {}

	return vb;
}

IndexBuffer* RenderSystem::CreateIndexBuffer(void* list_indices, UINT size_list) {
	IndexBuffer * ib = nullptr;
	try {
		ib = new IndexBuffer(list_indices, size_list, this);
	}
	catch (...) {}

	return ib;
}

ConstantBuffer* RenderSystem::CreateConstantBuffer(void* buffer, UINT size_buffer) {
	ConstantBuffer * cb = nullptr;
	try {
		cb = new ConstantBuffer(buffer, size_buffer, this);
	}
	catch (...) {}

	return cb;
}

VertexShader* RenderSystem::CreateVertexShader(const void* shader_byte_code, size_t byte_code_size) {
	VertexShader* vs = nullptr;
	try {
		vs = new VertexShader(shader_byte_code, byte_code_size, this);
	}
	catch (...) {}

	return vs;
}

PixelShader* RenderSystem::CreatePixelShader(const void* shader_byte_code, size_t byte_code_size) {
	PixelShader* ps = nullptr;
	try {
		ps = new PixelShader(shader_byte_code, byte_code_size, this);
	}
	catch (...) {}

	return ps;
}

bool RenderSystem::CompileVertexShader(const wchar_t* fileName, const char* entryPoint, void** shader_byte_code, size_t* byte_code_size) {
	ID3DBlob* errorBlob = nullptr;

	if (!SUCCEEDED(D3DCompileFromFile(fileName, nullptr, nullptr, entryPoint,
		"vs_5_0", 0, 0, &m_blob, &errorBlob)))
	{
		if (errorBlob)
			errorBlob->Release();

		return false;
	}

	*shader_byte_code = m_blob->GetBufferPointer();
	*byte_code_size = m_blob->GetBufferSize();

	return true;
}

bool RenderSystem::CompilePixelShader(const wchar_t* fileName, const char* entryPoint, void** shader_byte_code, size_t* byte_code_size) {
	ID3DBlob* errorBlob = nullptr;

	if (!SUCCEEDED(D3DCompileFromFile(fileName, nullptr, nullptr, entryPoint,
		"ps_5_0", 0, 0, &m_blob, &errorBlob)))
	{
		if (errorBlob)
			errorBlob->Release();

		return false;
	}

	*shader_byte_code = m_blob->GetBufferPointer();
	*byte_code_size = m_blob->GetBufferSize();

	return true;
}

void RenderSystem::ReleaseCompiledShader() {
	if (m_blob)
		m_blob->Release();
}

RenderSystem::~RenderSystem() {

}