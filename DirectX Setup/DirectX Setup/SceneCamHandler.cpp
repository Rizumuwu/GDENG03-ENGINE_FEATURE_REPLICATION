#include "SceneCamHandler.h"
#include <iostream>
#include "InputSystem.h"

SceneCamHandler* SceneCamHandler::sharedInstance = nullptr;

SceneCamHandler* SceneCamHandler::GetInstance() {
    if (sharedInstance == nullptr)
    {
        sharedInstance = new SceneCamHandler();
        sharedInstance->sceneCam = new Camera("Scene Camera");
    }
    return sharedInstance;
}

void SceneCamHandler::Initialize() {
    if (sharedInstance == nullptr) {
        sharedInstance = new SceneCamHandler();
    }

    if (sharedInstance->sceneCam == nullptr) {
        sharedInstance->sceneCam = new Camera("Scene Camera");
        InputSystem::get()->AddListener(sharedInstance->sceneCam);
    }
}

void SceneCamHandler::Destroy() {
    if (sharedInstance != nullptr) {
        delete sharedInstance->sceneCam;
        delete sharedInstance;
        sharedInstance = nullptr;
    }
}

void SceneCamHandler::Update(float deltaTime) {
    if (sharedInstance != nullptr && sharedInstance->sceneCam != nullptr) {
        sharedInstance->sceneCam->Update(deltaTime);
    }
}

Matrix4x4 SceneCamHandler::GetSceneCamViewMatrix() {
    if (sharedInstance != nullptr && sharedInstance->sceneCam != nullptr) {
        return sharedInstance->sceneCam->GetViewMatrix();
    }
    return Matrix4x4();  // Return identity matrix
}

SceneCamHandler::SceneCamHandler() {

}

SceneCamHandler::~SceneCamHandler() {

}
