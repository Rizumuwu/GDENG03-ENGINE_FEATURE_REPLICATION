#pragma once
#include <d3d11.h>

#include "Prerequisites.h"
#include "RenderSystem.h"

class GraphicsEngine {
public:
	GraphicsEngine();
	bool init();
	bool release();
	RenderSystem* GetRenderSystem();
	~GraphicsEngine();
public:
	static GraphicsEngine* get();
private:
	RenderSystem* m_render_system = nullptr;
};