#include "EngineTime.h"

EngineTime* EngineTime::sharedInstance = nullptr;

// Constructor
EngineTime::EngineTime() {
    start = std::chrono::system_clock::now();
}

// Destructor
EngineTime::~EngineTime() {}

// Initializes the EngineTime instance
void EngineTime::Initialize() {
    if (!sharedInstance) {
        sharedInstance = new EngineTime();
    }
}

// Calculates the delta time between frames
void EngineTime::GetDeltaTime() {
    if (!sharedInstance) return;

    sharedInstance->end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedTime = sharedInstance->end - sharedInstance->start;
    sharedInstance->deltaTime = elapsedTime.count();
    sharedInstance->start = sharedInstance->end;

    sharedInstance->frames++;

    //PrintData();
}

// Logs frame start (optional, you can use this for debugging)
void EngineTime::LogFrameStart() {
    std::cout << "Frame started at: " << std::chrono::system_clock::to_time_t(sharedInstance->start) << "\n";
}

// Logs frame end (optional, you can use this for debugging)
void EngineTime::LogFrameEnd() {
    std::cout << "Frame ended at: " << std::chrono::system_clock::to_time_t(sharedInstance->end) << "\n";
}

void EngineTime::PrintData() {
    std::cout << "Frame: " << sharedInstance->frames
        << " | Delta Time: " << sharedInstance->deltaTime << " seconds" << "\n";
}