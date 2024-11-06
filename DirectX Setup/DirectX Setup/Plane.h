#pragma once
#include "AGameObject.h"
#include "Matrix4x4.h"

class VertexBuffer;
class IndexBuffer;
class ConstantBuffer;
class VertexShader;
class PixelShader;

class Plane : public AGameObject {
public:
    Plane(std::string name, float width, float height, float zPos);
    ~Plane();

    void Update(float deltaTime) override;
    void Draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader) override;
    void SetAnimSpeed(float speed);

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

    Vector3D GetRandomPosition(float rangeX, float rangeY, float rangeZ);

    Matrix4x4 m_world_cam;
};
