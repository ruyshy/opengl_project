#include <pch.h>
#include <Game/Game.h>

MainWindow::MainWindow()
{
	mpProjectionMatrix = new mat4(1.0f);
	mpWidth = make_shared<int>(0);
	mpHeight = make_shared<int>(0);
	
	mpGame = make_unique<Game>(this);
}

MainWindow::~MainWindow()
{
	NULLPTR_CHECK_DELETE(mpProjectionMatrix);
}

void MainWindow::initializeScene()
{
	glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glEnable(GL_SCISSOR_TEST);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	
	glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);

	mpGame->initialize();
}

void MainWindow::renderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	mpGame->Render();
}

void MainWindow::updateScene()
{
	
	if (keyPressedOnce(GLFW_KEY_F3)) {
		setVerticalSynchronization(!isVerticalSynchronizationEnabled());
	}
	mpGame->Update();

	std::string windowTitleWithFPS = "FPS: "
		+ std::to_string(getFPS()) +
		", VSync: " + (isVerticalSynchronizationEnabled() ? "On" : "Off") + " (Press F3 to toggle)";
	glfwSetWindowTitle(getWindow(), windowTitleWithFPS.c_str());
}

void MainWindow::releaseScene()
{

}

void MainWindow::onWindowSizeChanged(int width, int height)
{
	*mpProjectionMatrix = getOrthoProjectionMatrix();
	*mpWidth = width;
	*mpHeight = height;
}

void MainWindow::onMouseButtonPressed(int button, int action)
{

}

mat4* MainWindow::GetProjectionMatrix() { return mpProjectionMatrix; }
shared_ptr<int> MainWindow::GetWidth() { return mpWidth; }
shared_ptr<int> MainWindow::GetHeight() { return mpHeight; }
