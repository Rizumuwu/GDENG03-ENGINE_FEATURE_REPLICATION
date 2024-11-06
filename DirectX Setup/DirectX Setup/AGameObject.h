#pragma once
#include <string>
#include "Vector3D.h"

class VertexShader;
class PixelShader;

class AGameObject {
public:
	AGameObject(std::string name);
	~AGameObject();

	virtual void Update(float deltaTime) = 0;
	virtual void Draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader) = 0;

	void SetPosition(float x, float y, float z);
	void SetPosition(Vector3D pos);
	Vector3D GetLocalPosition();

	void SetScale(float x, float y, float z);
	void SetScale(Vector3D scale);
	Vector3D GetLocalScale();

	void SetRotation(float x, float y, float z);
	void SetRotation(Vector3D rot);
	Vector3D GetLocalRotation();

private:
	std::string name;
	Vector3D localRot;
	Vector3D localPos;
	Vector3D localScale;
};

