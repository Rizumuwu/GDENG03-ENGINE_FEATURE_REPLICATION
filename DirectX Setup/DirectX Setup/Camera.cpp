#define VK_SPACE 0x20
#define VK_LSHIFT 0xA0

#include "Camera.h"
#include "InputSystem.h"
#include <iostream>
#include <algorithm>

Camera::Camera(string camera) : AGameObject(camera) {
    moveSpeed = regularSpeed;
}

Camera::~Camera() {

}

void Camera::Update(float deltaTime) {

}

Matrix4x4 Camera::GetViewMatrix() {
    return this->localMatrix;
}

void Camera::OnKeyDown(int key) {
    if (key == 'W') {
        m_forward = 1.0f;
    }
    if (key == 'S') {
        m_forward = -1.0f;
    }
    if (key == 'A') {
        m_rightward = -1.0f;
    }
    if (key == 'D') {
        m_rightward = 1.0f;
    }
    if (key == VK_SPACE) {
        m_upward = 1.0f;
    }
    if (key == VK_LSHIFT) {
        moveSpeed = sprintSpeed;
    }
    this->UpdateViewMatrix();
}

void Camera::OnKeyUp(int key) {
    if (key == 'W') {
        m_forward = 0.0f;
    }
    if (key == 'S') {
        m_forward = 0.0f;
    }
    if (key == 'A') {
        m_rightward = 0.0f;
    }
    if (key == 'D') {
        m_rightward = 0.0f;
    }
    if (key == VK_SPACE) {
        m_upward = 0.0f;
    }
    if (key == VK_LSHIFT) {
        moveSpeed = regularSpeed;
    }
    this->UpdateViewMatrix();
}

void Camera::OnMouseMove(const Point& mouse_pos) {
    if (m_rightMousePressed) {
        float deltaX = mouse_pos.m_x - m_lastMousePos.m_x;
        float deltaY = mouse_pos.m_y - m_lastMousePos.m_y;

        m_rotX += deltaY * 0.01f;
        m_rotY += deltaX * 0.01f;

        m_rotX = std::clamp(m_rotX, -89.0f, 89.0f);
    }
    m_lastMousePos = mouse_pos;

    this->UpdateViewMatrix();
}

void Camera::OnLeftMouseDown(const Point& mouse_pos) {

}

void Camera::OnLeftMouseUp(const Point& mouse_pos) {

}

void Camera::OnRightMouseDown(const Point& mouse_pos) {
    m_rightMousePressed = true;
    m_lastMousePos = mouse_pos;
}

void Camera::OnRightMouseUp(const Point& mouse_pos) {
    m_rightMousePressed = false;
}

void Camera::Draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader) {

}

void Camera::UpdateViewMatrix() {
    Matrix4x4 worldCam;
    worldCam.SetIdentity();
    Matrix4x4 temp;

    temp.SetIdentity();
    temp.SetRotationX(m_rotX);
    worldCam *= temp;

    temp.SetIdentity();
    temp.SetRotationY(m_rotY);
    worldCam *= temp;

    Vector3D newPos;
    newPos = this->GetLocalPosition() + (worldCam.GetZDirection() * (m_forward * moveSpeed));
    newPos = newPos + (worldCam.GetXDirection() * (m_rightward * moveSpeed));
    newPos = newPos + (Vector3D(0.0f, m_upward * moveSpeed, 0.0f));

    temp.SetIdentity();
    temp.SetTranslation(newPos);
    worldCam *= temp;

    worldCam.Inverse();
    this->SetPosition(newPos);
    this->localMatrix = worldCam;
}
