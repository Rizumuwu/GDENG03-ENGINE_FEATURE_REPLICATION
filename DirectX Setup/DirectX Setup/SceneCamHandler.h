#pragma once
#include "Camera.h"

class SceneCamHandler {
public:
	static SceneCamHandler* GetInstance();
	static void Initialize();
	static void Destroy();

	void Update(float deltaTime);

	Matrix4x4 GetSceneCamViewMatrix();

private:
	SceneCamHandler();
	~SceneCamHandler();
	SceneCamHandler(SceneCamHandler const&) {};
	SceneCamHandler& operator=(SceneCamHandler const&) {};
	static SceneCamHandler* sharedInstance;

	Camera* sceneCam;
};