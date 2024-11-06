#include "AppWindow.h"
#include "EngineTime.h"
#include "SceneCamHandler.h"

int main() {
	AppWindow app;

	if (app.init()) 
	{
		EngineTime::Initialize();
		SceneCamHandler::Initialize();

		while (app.IsRunning()) 
		{
			EngineTime::GetDeltaTime();

			app.broadcast();
		}
	}

	return 0;
}
