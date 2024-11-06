#pragma once
#include <vector>

#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "IndexBuffer.h"
#include "InputListener.h"

class Cube;
class Plane;

class AppWindow : public Window, public InputListener
{
public:
	AppWindow();
	~AppWindow();

	void UpdateCam();

	// Inherited via Window
	virtual void OnCreate() override;
	virtual void OnUpdate() override;
	virtual	void OnDestroy() override;
	virtual void OnFocus() override;
	virtual void OnKillFocus() override;

	// Inherited via InputListener
	void OnKeyDown(int key) override;
	void OnKeyUp(int key) override;
	virtual void OnMouseMove(const Point& mouse_pos) override;

	virtual void OnLeftMouseDown(const Point& mouse_pos) override;
	virtual void OnLeftMouseUp(const Point& mouse_pos) override;
	virtual void OnRightMouseDown(const Point& mouse_pos) override;
	virtual void OnRightMouseUp(const Point& mouse_pos) override;

	void IncreaseSpeed();
	void AlterX(float newVal);
	void AlterY(float newVal);
	void AlterScale(float newVal);
	void AlterForward(float newVal);
	void AlterRightward(float newVal);

private:
	SwapChain* m_swap_chain;
	VertexBuffer* m_vb;
	VertexShader* m_vs;
	PixelShader* m_ps;
	ConstantBuffer* m_cb;
	IndexBuffer* m_ib;

	float animationMultiplier = 0.0f;
	float m_old_delta;
	float m_new_delta;
	float m_delta_time;

	float m_delta_pos;
	float m_delta_scale;

	std::vector<Cube> cubeList;
	std::vector<Plane> planeList;
};