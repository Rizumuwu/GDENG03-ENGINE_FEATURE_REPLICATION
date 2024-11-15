#pragma once
#include <d3d11.h>

#include "Prerequisites.h"


class DeviceContext {
public:
	DeviceContext(ID3D11DeviceContext* device_context, RenderSystem* system);
	void clearRenderTargetColor(SwapChain* swapChain, float red, float green, float blue, float alpha);
	void SetVertexBuffer(VertexBuffer* vertex_buffer);

	void SetIndexBuffer(IndexBuffer* index_buffer);

	void DrawTriangleList(UINT vertex_count, UINT start_vertex_index);
	void DrawIndexedTriangleList(UINT index_count, UINT start_vertex_index, UINT start_index_location);
	void DrawTriangleStrip(UINT vertex_count, UINT start_vertex_index);

	void SetViewportSize(UINT width, UINT height);

	void SetVertexShader(VertexShader* vertexShader);
	void SetPixelShader(PixelShader* pixelShader);

	void SetConstantBuffer(VertexShader* vertexShader, ConstantBuffer* buffer);
	void SetConstantBuffer(PixelShader* pixelShader, ConstantBuffer* buffer);

	~DeviceContext();
private:
	ID3D11DeviceContext* m_device_context;
	RenderSystem* m_system = nullptr;
private:
	friend class ConstantBuffer;
};