#include "pch.h"
#include "MainWindow.h"

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
	#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
	#define DBG_NEW new
#endif
int main(int argc, char* path[])
{
	//_CrtSetBreakAlloc(1345);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);	

	const std::string& windowTitle = "Title";
	int majorVersion = 4;
	int minorVersion = 6;

	unique_ptr<MainWindow> window = make_unique<MainWindow>();

	if (!window->createOpenGLWindow(windowTitle, majorVersion, minorVersion, 640, 480))
	{
		printf("Failed to create window with OpenGL context %d.%d! Shutting down...\n", majorVersion, minorVersion);
		return 0;
	}

	window->runApp();

	//_CrtDumpMemoryLeaks();

	return 0;
}