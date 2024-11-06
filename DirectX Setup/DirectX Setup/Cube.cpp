#include "Cube.h"
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

Cube::Cube(std::string name, float width, float height, int num) : AGameObject(name) {
	this->width = width;
	this->height = height;

	this->cubeNum = num;

	//position = GetRandomPosition(15.0f, 15.0f, 10.0f);
	position = Vector3D(-1.5f, 0.5f, -1.5f);


	// cam stuff
	m_world_cam.SetTranslation(Vector3D(0, 0, -2));

	Vertex vertex_list[] =
	{
		//X - Y - Z
		// Front face
		{Vector3D(-0.5f,-0.5f,-0.5f),   Vector3D(1,1,1), Vector3D(0,1,0) },
		{Vector3D(-0.5f,0.5f,-0.5f),    Vector3D(1,1,1), Vector3D(0,1,1) },
		{Vector3D(0.5f,0.5f,-0.5f),   Vector3D(1,1,1),  Vector3D(1,0,0) },
		{Vector3D(0.5f,-0.5f,-0.5f),    Vector3D(1,1,1), Vector3D(0,0,1) },


		// Back face
		{Vector3D(0.5f,-0.5f,0.5f),   Vector3D(0.6,0.6,0.6), Vector3D(0,0,1) },
		{Vector3D(0.5f,0.5f,0.5f),    Vector3D(0.6,0.6,0.6), Vector3D(0,0,1) },
		{Vector3D(-0.5f,0.5f,0.5f),    Vector3D(0.6,0.6,0.6), Vector3D(0,0,1) },
		{Vector3D(-0.5f,-0.5f,0.5f),   Vector3D(0.6,0.6,0.6), Vector3D(0,0,1) }
	};

	UINT size_list = ARRAYSIZE(vertex_list);

	unsigned int index_list[] = {
		//Front side
		0, 1, 2, //triangle 1
		2, 3, 0, //triangle 2
		//Back side
		4, 5, 6,
		6, 7, 4,
		//Top side
		1, 6, 5,
		5, 2, 1,
		//Bottom side
		7, 0, 3,
		3, 4, 7,
		//Right side
		3, 2, 5,
		5, 4, 3,
		//Left side
		7, 6, 1,
		1, 0, 7
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

Cube::~Cube() {

}

void Cube::Update(float deltaTime) {
	Constant cc;
	static float accumulatedTime = 0.0f;
	accumulatedTime += EngineTime::sharedInstance->deltaTime * speed;
	cc.m_time = accumulatedTime;

	//m_delta_pos += EngineTime::sharedInstance->deltaTime / 4.0f;
	//if (m_delta_pos > 1.0f)
	//	m_delta_pos = 0.0f;
	
	Matrix4x4 temp;
	m_delta_scale += deltaTime / 1.0;

	cc.m_world.SetIdentity();

	Matrix4x4 world_cam;
	world_cam.SetIdentity();

	temp.SetIdentity();
	temp.SetScale(Vector3D(1.0f, 1.0f, 1.0f));
	world_cam *= temp;

	float radians = cardRot * (3.14159265358979323846f / 180.0f);

	//temp.SetIdentity();
	//temp.SetRotationX(radians);
	//world_cam *= temp;

	//temp.SetIdentity();
	//temp.SetRotationY(m_delta_scale);
	//world_cam *= temp;

	//temp.SetIdentity();
	//temp.SetRotationZ(m_delta_scale);
	//world_cam *= temp;

	Vector3D new_pos = position;
	
	new_pos = new_pos + world_cam.GetZDirection() * (m_forward * 0.3f);
	new_pos = new_pos + world_cam.GetXDirection() * (m_rightward * 0.3f);

	world_cam.SetTranslation(new_pos);

	m_world_cam = world_cam;

	cc.m_world *= m_world_cam;

	cc.m_view = SceneCamHandler::GetInstance()->GetSceneCamViewMatrix();

	cc.m_proj.SetPerspectiveFovLH(1.57f, ((float)width / (float)height), 0.1f, 100.0f);

	m_cb->update(GraphicsEngine::get()->GetRenderSystem()->GetImmediateDeviceContext(), &cc);
}

void Cube::Draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader) {
	GraphicsEngine::get()->GetRenderSystem()->GetImmediateDeviceContext()->SetConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->GetRenderSystem()->GetImmediateDeviceContext()->SetConstantBuffer(m_ps, m_cb);

	GraphicsEngine::get()->GetRenderSystem()->GetImmediateDeviceContext()->SetVertexShader(m_vs);
	GraphicsEngine::get()->GetRenderSystem()->GetImmediateDeviceContext()->SetPixelShader(m_ps);


	GraphicsEngine::get()->GetRenderSystem()->GetImmediateDeviceContext()->SetVertexBuffer(m_vb);
	GraphicsEngine::get()->GetRenderSystem()->GetImmediateDeviceContext()->SetIndexBuffer(m_ib);

	GraphicsEngine::get()->GetRenderSystem()->GetImmediateDeviceContext()->DrawIndexedTriangleList(m_ib->GetSizeIndexList(), 0, 0);
}

void Cube::SetAnimSpeed(float speed) {
	this->speed = speed;
}

void Cube::SetXRotation(float newVal) {
	this->m_rot_x += newVal;
}

void Cube::SetYRotation(float newVal) {
	this->m_rot_y += newVal;
}

void Cube::SetScale(float newVal) {
	this->m_scale_cube = newVal;
}

void Cube::SetForward(float newVal) {
	this->m_forward = newVal;
}

void Cube::SetRightward(float newVal) {
	this->m_rightward = newVal;
}

Vector3D Cube::GetRandomPosition(float rangeX, float rangeY, float rangeZ) {

	float randomX = (rand() % 1000 / 1000.0f) * rangeX - (rangeX / 2);
	float randomY = (rand() % 1000 / 1000.0f) * rangeY - (rangeY / 2);
	float randomZ = (rand() % 1000 / 1000.0f) * rangeZ - (rangeZ / 2);

	return Vector3D(randomX, randomY, randomZ);
}