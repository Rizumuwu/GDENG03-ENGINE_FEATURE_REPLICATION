#include "AppWindow.h"
#include <Windows.h>

#include "Cube.h"
#include "Plane.h"
#include "EngineTime.h"
#include "Matrix4x4.h"
#include "InputSystem.h"
#include "SceneCamHandler.h"
#include "UIManager.h"

struct vertex {
	Vector3D position;
	Vector3D color;
	Vector3D color1;
};

__declspec(align(16))
struct constant {
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;
	unsigned int m_time;
};

AppWindow::AppWindow() {

}

AppWindow::~AppWindow() {

}

void AppWindow::UpdateCam() {

}

void AppWindow::OnCreate()
{
	Window::OnCreate();

	InputSystem::get()->AddListener(this);
	//InputSystem::get()->ShowCursor(false);

	GraphicsEngine::get()->init();
	RECT rc = this->getClientWindowRect();
	m_swap_chain = GraphicsEngine::get()->GetRenderSystem()->CreateSwapChain(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	float width = (this->getClientWindowRect().right - this->getClientWindowRect().left);
	float height = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);

	// Make cubes here
	for(int i = 0; i < 1; i++) {
		Cube tempCube("cube", width, height, i);
		cubeList.push_back(tempCube);
	}

	for (int i = 0; i < 1; i++) {
		Plane tempPlane("plane", width, height, 0.0f);
		planeList.push_back(tempPlane);
	}

	UIManager::GetInstance()->Init(this->m_hwnd);

	UIManager::GetInstance()->SpawnColorPicker();
	UIManager::GetInstance()->SpawnAnim();
	UIManager::GetInstance()->SpawnDetails();
	UIManager::GetInstance()->SpawnFiles();
	UIManager::GetInstance()->SpawnHeir();
	UIManager::GetInstance()->SpawnLog();
}

void AppWindow::OnUpdate() {

	Window::OnUpdate();

	InputSystem::get()->Update();

	SceneCamHandler::GetInstance()->Update(m_delta_time);

	GraphicsEngine::get()->GetRenderSystem()->GetImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0.2f, 0.2f, 0.2f, 1);

	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->GetRenderSystem()->GetImmediateDeviceContext()->SetViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	// Draw cubes here
	for (auto& i : cubeList)
	{
		i.Update(m_delta_time);
		i.Draw(0, 0, m_vs, m_ps);
	}

	for (auto& i : planeList)
	{
		i.Update(m_delta_time);
		i.Draw(0, 0, m_vs, m_ps);
	}

	UIManager::GetInstance()->DrawAllUI();

	m_swap_chain->present(true);

	m_old_delta = m_new_delta;
	m_new_delta = ::GetTickCount64();

	m_delta_time = (m_old_delta) ? ((m_new_delta - m_old_delta) / 1000.0f) : 0;
}

void AppWindow::OnDestroy()
{
	Window::OnDestroy();
	GraphicsEngine::get()->release();
}

void AppWindow::OnFocus() {
	InputSystem::get()->AddListener(this);
}

void AppWindow::OnKillFocus() {
	InputSystem::get()->RemoveListener(this);
}

void AppWindow::IncreaseSpeed() {

	static bool increasing = true;

	if(increasing) {
		this->animationMultiplier += 20.0f;
		if (this->animationMultiplier >= 10000.0f)
			increasing = false;
	}
	else {
		this->animationMultiplier -= 20.0f;
		if (this->animationMultiplier <= 0.0f)
			increasing = true;
	}

	this->animationMultiplier = 700.0f;
}

void AppWindow::AlterX(float newVal) {
	for (int i = 0; i < cubeList.size(); i++) {
		cubeList[i].SetXRotation(newVal);
	}
}

void AppWindow::AlterY(float newVal) {
	for (int i = 0; i < cubeList.size(); i++) {
		cubeList[i].SetYRotation(newVal);
	}
}

void AppWindow::AlterScale(float newVal) {
	for (int i = 0; i < cubeList.size(); i++) {
		cubeList[i].SetScale(newVal);
	}
}

void AppWindow::AlterForward(float newVal) {
	for (int i = 0; i < cubeList.size(); i++) {
		cubeList[i].SetForward(newVal);
	}
}

void AppWindow::AlterRightward(float newVal) {
	for (int i = 0; i < cubeList.size(); i++) {
		cubeList[i].SetRightward(newVal);
	}
}

void AppWindow::OnKeyDown(int key) {
	//if (key == 'W') {
	//	AlterForward(1.0f);
	//}
	//else if (key == 'S') {
	//	AlterForward(-1.0f);
	//}
	//else if (key == 'A') {
	//	AlterRightward(-1.0f);
	//}
	//else if (key == 'D') {
	//	AlterRightward(1.0f);
	//}
}

void AppWindow::OnKeyUp(int key) {
	//AlterForward(0.0f);
	//AlterRightward(0.0f);
}

void AppWindow::OnMouseMove(const Point& mouse_pos) {
	//float width = (this->getClientWindowRect().right - this->getClientWindowRect().left);
	//float height = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);

	//AlterX((mouse_pos.m_y - (height / 2.0f)) * m_delta_time * 0.1f);
	//AlterY((mouse_pos.m_x - (width / 2.0f)) * m_delta_time * 0.1f);

	//InputSystem::get()->SetCursorPos(Point(width / 2.0f, height / 2.0f));
}

void AppWindow::OnLeftMouseDown(const Point& mouse_pos) {
	AlterScale(0.5f);
}

void AppWindow::OnLeftMouseUp(const Point& mouse_pos) {
	AlterScale(1.0f);
}

void AppWindow::OnRightMouseDown(const Point& mouse_pos) {
	AlterScale(2.0f);
}

void AppWindow::OnRightMouseUp(const Point& mouse_pos) {
	AlterScale(1.0f);
}
