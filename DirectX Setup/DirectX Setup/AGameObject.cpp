#include "AGameObject.h"

AGameObject::AGameObject(std::string name) {
	this->name = name;
	this->localRot = Vector3D::Zeros();
	this->localPos = Vector3D::Zeros();
	this->localScale = Vector3D::Ones();
}

AGameObject::~AGameObject(){
	
}

void AGameObject::SetPosition(float x, float y, float z) {
	this->localPos = Vector3D(x, y, z);
}

void AGameObject::SetPosition(Vector3D pos) {
	this->localPos = pos;
}

Vector3D AGameObject::GetLocalPosition() {
	return this->localPos;
}

void AGameObject::SetScale(float x, float y, float z) {
	this->localScale = Vector3D(x, y, z);
}

void AGameObject::SetScale(Vector3D scale) {
	this->localScale = scale;
}

Vector3D AGameObject::GetLocalScale() {
	return this->localScale;
}

void AGameObject::SetRotation(float x, float y, float z) {
	this->localRot = Vector3D(x, y, z);
}

void AGameObject::SetRotation(Vector3D rot) {
	this->localRot = rot;
}

Vector3D AGameObject::GetLocalRotation() {
	return this->localRot;
}

