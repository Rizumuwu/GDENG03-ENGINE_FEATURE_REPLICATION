#include "GraphicsEngine.h"
#include "RenderSystem.h"

#pragma comment(lib, "D3DCompiler.lib")
#pragma comment(lib, "d3d11.lib")

GraphicsEngine::GraphicsEngine() {

}

bool GraphicsEngine::init() {
	m_render_system = new RenderSystem();
	m_render_system->init();
	return true;
}

bool GraphicsEngine::release() {
	delete m_render_system;
	return true;
}

RenderSystem* GraphicsEngine::GetRenderSystem()
{
	return m_render_system;
}

GraphicsEngine* GraphicsEngine::get() {
	static GraphicsEngine engine;
	return &engine;
}

GraphicsEngine::~GraphicsEngine() {

}