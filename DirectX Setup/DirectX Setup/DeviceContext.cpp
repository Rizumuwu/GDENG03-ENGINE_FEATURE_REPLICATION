#include "DeviceContext.h"
#include "SwapChain.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "IndexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include <exception>

DeviceContext::DeviceContext(ID3D11DeviceContext* device_context, RenderSystem* system) : m_system(system), m_device_context(device_context) {
	
}

void DeviceContext::clearRenderTargetColor(SwapChain* swapChain, float red, float green, float blue, float alpha) {
	FLOAT clear_color[] = { red, green, blue, alpha };

	m_device_context->ClearRenderTargetView(swapChain->m_rtv, clear_color);
	m_device_context->ClearDepthStencilView(swapChain->m_dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
	m_device_context->OMSetRenderTargets(1, &swapChain->m_rtv, swapChain->m_dsv);
}

void DeviceContext::SetVertexBuffer(VertexBuffer* vertex_buffer) {
	UINT stride = vertex_buffer->m_size_vertex;
	UINT offset = 0;

	m_device_context->IASetVertexBuffers(0, 1, &vertex_buffer->m_buffer, &stride, &offset);
	m_device_context->IASetInputLayout(vertex_buffer->m_layout);
}

void DeviceContext::SetIndexBuffer(IndexBuffer* index_buffer) {
	m_device_context->IASetIndexBuffer(index_buffer->m_buffer, DXGI_FORMAT_R32_UINT, 0);
}

void DeviceContext::DrawTriangleList(UINT vertex_count, UINT start_vertex_index) {
	m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_device_context->Draw(vertex_count, start_vertex_index);
}

void DeviceContext::DrawIndexedTriangleList(UINT index_count, UINT start_vertex_index, UINT start_index_location) {
	m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_device_context->DrawIndexed(index_count, start_index_location, start_vertex_index);
}

void DeviceContext::DrawTriangleStrip(UINT vertex_count, UINT start_vertex_index) {
	m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	m_device_context->Draw(vertex_count, start_vertex_index);
}

void DeviceContext::SetViewportSize(UINT width, UINT height) {
	D3D11_VIEWPORT vp = {};
	vp.Width = (FLOAT)width;
	vp.Height = (FLOAT)height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	m_device_context->RSSetViewports(1, &vp);
}

void DeviceContext::SetVertexShader(VertexShader* vertexShader) {
	m_device_context->VSSetShader(vertexShader->m_vs, nullptr, 0);
}

void DeviceContext::SetPixelShader(PixelShader* pixelShader) {
	m_device_context->PSSetShader(pixelShader->m_ps, nullptr, 0);
}

void DeviceContext::SetConstantBuffer(VertexShader* vertexShader, ConstantBuffer* buffer) {
	m_device_context->VSSetConstantBuffers(0, 1, &buffer->m_buffer);
}

void DeviceContext::SetConstantBuffer(PixelShader* pixelShader, ConstantBuffer* buffer) {
	m_device_context->PSSetConstantBuffers(0, 1, &buffer->m_buffer);
}

DeviceContext::~DeviceContext() {
	m_device_context->Release();
}
