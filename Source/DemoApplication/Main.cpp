#include "Demo.h"

int main()
{
	OrbEngine::Demo demo(1000, 800, 60.0f);
	bool success = demo.InitializeApplication();

	if (!success) return 1;

	while (demo.IsRunning())
	{
		demo.RunLoop();
	}

	demo.Shutdown();
	return 0;
}