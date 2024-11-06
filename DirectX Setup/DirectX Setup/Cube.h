#pragma once
#include "AGameObject.h"
#include "Matrix4x4.h"

class VertexBuffer;
class IndexBuffer;
class ConstantBuffer;
class VertexShader;
class PixelShader;

class Cube : public AGameObject {
public:
	Cube(std::string name, float width, float height, int num);
	~Cube();

	void Update(float deltaTime) override;
	void Draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader) override;
	void SetAnimSpeed(float speed);
	void SetXRotation(float newVal);
	void SetYRotation(float newVal);
	void SetScale(float newVal);
	void SetForward(float newVal);
	void SetRightward(float newVal);

private:
	VertexBuffer* m_vb;
	IndexBuffer* m_ib;
	ConstantBuffer* m_cb;
	VertexShader* m_vs;
	PixelShader* m_ps;

	Vector3D position;

	float ticks = 0.0f;
	float deltaPos = 0.0f;
	float deltaTime = 0.0f;
	float speed = 10.0f;
	float m_delta_scale;
	float rotationSpeed = 0;

	float width;
	float height;

	float m_rot_x = 0.0f;
	float m_rot_y = 0.0f;

	float m_scale_cube = 1;

	Vector3D GetRandomPosition(float rangeX, float rangeY, float rangeZ);

	// cam stuff
	Matrix4x4 m_world_cam;
	float m_forward = 0.0f;
	float m_rightward = 0.0f;

	float m_delta_pos = 0.0f;
	float m_delta_time = 0.0f;

	int cubeNum = 0;
	float cardRot = 0.0f;
};

