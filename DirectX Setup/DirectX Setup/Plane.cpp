#include "Plane.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "Matrix4x4.h"
#include "DeviceContext.h"
#include "EngineTime.h"
#include "SceneCamHandler.h"

struct Vertex {
    Vector3D position;
    Vector3D color;
    Vector3D color1;
};

__declspec(align(16))
struct Constant {
    Matrix4x4 m_world;
    Matrix4x4 m_view;
    Matrix4x4 m_proj;
    unsigned int m_time;
};

Plane::Plane(std::string name, float width, float height, float zPos) : AGameObject(name) {
    this->width = width;
    this->height = height;

    Vertex vertex_list[] =
    {
        // X - Y - Z
        {Vector3D(-0.5f, -0.5f, zPos), Vector3D(0.7,0.7,0.7), Vector3D(1,1,1) },  // Bottom left
        {Vector3D(-0.5f,  0.5f, zPos), Vector3D(0.4,0.4,0.4), Vector3D(1,1,1) },  // Top left
        {Vector3D(0.5f,  0.5f, zPos), Vector3D(0.2,0.2,0.2), Vector3D(1,1,1) },  // Top right
        {Vector3D(0.5f, -0.5f, zPos), Vector3D(0.4,0.4,0.4), Vector3D(1,1,1) }   // Bottom right
    };

    UINT size_list = ARRAYSIZE(vertex_list);

    unsigned int index_list[] = {
        0, 1, 2,  // Triangle 1
        2, 3, 0   // Triangle 2
    };

    UINT size_index_list = ARRAYSIZE(index_list);
    m_ib = GraphicsEngine::get()->GetRenderSystem()->CreateIndexBuffer(index_list, size_index_list);

    void* shader_byte_code = nullptr;
    size_t size_shader = 0;

    GraphicsEngine::get()->GetRenderSystem()->CompileVertexShader(L"VertexShader.hlsl", "VSMain", &shader_byte_code, &size_shader);
    m_vs = GraphicsEngine::get()->GetRenderSystem()->CreateVertexShader(shader_byte_code, size_shader);
    m_vb = GraphicsEngine::get()->GetRenderSystem()->CreateVertexBuffer(vertex_list, sizeof(Vertex), size_list, shader_byte_code, size_shader);
    GraphicsEngine::get()->GetRenderSystem()->ReleaseCompiledShader();

    GraphicsEngine::get()->GetRenderSystem()->CompilePixelShader(L"PixelShader.hlsl", "PSMain", &shader_byte_code, &size_shader);
    m_ps = GraphicsEngine::get()->GetRenderSystem()->CreatePixelShader(shader_byte_code, size_shader);
    GraphicsEngine::get()->GetRenderSystem()->ReleaseCompiledShader();

    Constant cc;
    cc.m_time = 0;

    m_cb = GraphicsEngine::get()->GetRenderSystem()->CreateConstantBuffer(&cc, sizeof(Constant));
}

Plane::~Plane() {

}

void Plane::Update(float deltaTime) {
    Constant cc;
    static float accumulatedTime = 0.0f;
    accumulatedTime += EngineTime::sharedInstance->deltaTime * speed;
    cc.m_time = accumulatedTime;

    Matrix4x4 temp;
    m_delta_scale += deltaTime / 1.0;

    cc.m_world.SetIdentity();

    Matrix4x4 world_cam;
    world_cam.SetIdentity();

    temp.SetIdentity();
    temp.SetScale(Vector3D(9, 9, 9));
    world_cam *= temp;

    float radians = 90 * (3.14159265358979323846f / 180.0f);

    temp.SetIdentity();
    temp.SetRotationX(radians);
    world_cam *= temp;

    temp.SetIdentity();
    temp.SetRotationY(0);
    world_cam *= temp;

    Vector3D new_pos = position;

    new_pos = new_pos + world_cam.GetZDirection() * (0 * 0.3f);
    new_pos = new_pos + world_cam.GetXDirection() * (0 * 0.3f);

    world_cam.SetTranslation(new_pos);

    m_world_cam = world_cam;

    cc.m_world *= m_world_cam;

    cc.m_view = SceneCamHandler::GetInstance()->GetSceneCamViewMatrix();

    cc.m_proj.SetPerspectiveFovLH(1.57f, ((float)width / (float)height), 0.1f, 100.0f);

    m_cb->update(GraphicsEngine::get()->GetRenderSystem()->GetImmediateDeviceContext(), &cc);
}

void Plane::Draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader) {
    GraphicsEngine::get()->GetRenderSystem()->GetImmediateDeviceContext()->SetConstantBuffer(m_vs, m_cb);
    GraphicsEngine::get()->GetRenderSystem()->GetImmediateDeviceContext()->SetConstantBuffer(m_ps, m_cb);

    GraphicsEngine::get()->GetRenderSystem()->GetImmediateDeviceContext()->SetVertexShader(m_vs);
    GraphicsEngine::get()->GetRenderSystem()->GetImmediateDeviceContext()->SetPixelShader(m_ps);

    GraphicsEngine::get()->GetRenderSystem()->GetImmediateDeviceContext()->SetVertexBuffer(m_vb);
    GraphicsEngine::get()->GetRenderSystem()->GetImmediateDeviceContext()->SetIndexBuffer(m_ib);

    GraphicsEngine::get()->GetRenderSystem()->GetImmediateDeviceContext()->DrawIndexedTriangleList(m_ib->GetSizeIndexList(), 0, 0);
}

void Plane::SetAnimSpeed(float speed) {
    this->speed = speed;
}

Vector3D Plane::GetRandomPosition(float rangeX, float rangeY, float rangeZ) {
    float randomX = (rand() % 1000 / 1000.0f) * rangeX - (rangeX / 2);
    float randomY = (rand() % 1000 / 1000.0f) * rangeY - (rangeY / 2);

    return Vector3D(randomX, randomY, 0.0f);  // Z is always 0 for a 2D plane
}
