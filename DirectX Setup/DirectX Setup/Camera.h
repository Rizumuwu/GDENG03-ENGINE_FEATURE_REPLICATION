#pragma once
#include "AGameObject.h"
#include <string>
#include "InputListener.h"
#include "Matrix4x4.h"

using namespace std;

class Camera : public AGameObject, public InputListener {
public:
	Camera(string camera);
	~Camera();

	void Update(float deltaTime) override;
	Matrix4x4 GetViewMatrix();

	virtual void OnKeyDown(int key) override;
	virtual void OnKeyUp(int key) override;

	virtual void OnMouseMove(const Point& mouse_pos) override;
	virtual void OnLeftMouseDown(const Point& mouse_pos) override;
	virtual void OnLeftMouseUp(const Point& mouse_pos) override;
	virtual void OnRightMouseDown(const Point& mouse_pos) override;
	virtual void OnRightMouseUp(const Point& mouse_pos) override;

	virtual void Draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader) override;
private:
	void UpdateViewMatrix();
	Matrix4x4 localMatrix;

	float m_rotX = 0.0f;
	float m_rotY = 0.0f;
	bool m_rightMousePressed = false;
	Point m_lastMousePos;

	float m_forward = 0.0f;
	float m_rightward = 0.0f;
	float m_upward = 0.0f;

	float moveSpeed = 0;
	float regularSpeed = 0.02f;
	float sprintSpeed = 0.05f;
};

