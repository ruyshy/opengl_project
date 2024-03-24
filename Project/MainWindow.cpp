#include "pch.h"
#include "MainWindow.h"
#include "Shader.h"
#include "Sprite.h"
#include "Quad.h"

#include "ResourceManager.h"
#include "shader_resource.h"

#include <glm/gtc/matrix_transform.hpp>
#include "stb_image.h"

MainWindow::MainWindow()
{
	mpProjectionMatrix = new glm::mat4(1.0f);
	mpWidth = new int(0);
	mpHeight = new int(0);
}

MainWindow::~MainWindow()
{
	NULLPTR_CHECK_DELETE(mpProjectionMatrix);
	NULLPTR_CHECK_DELETE(mpWidth);
	NULLPTR_CHECK_DELETE(mpHeight);
}

void MainWindow::initializeScene()
{
	glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	mpCheckboard = new Shader(
		ResourceManager::GetResourceString(IDR_SHADER_CHECKBOARD_VS, Resource::SHADER),
		ResourceManager::GetResourceString(IDR_SHADER_CHECKBOARD_FS, Resource::SHADER));

	rect = VertexBufferSystem2D::Generate();

}

void MainWindow::renderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mpCheckboard->use();
	mpCheckboard->setMat4("projection", getOrthoProjectionMatrix());
	mpCheckboard->setMat4("model_matrx", glm::scale(glm::mat4(1), glm::vec3(getScreenWidth(), getScreenHeight(), 1)));
	mpCheckboard->setVec2("resolution", glm::vec2(getScreenWidth(), getScreenHeight()));
	rect.draw();

}

void MainWindow::updateScene()
{

	if (keyPressedOnce(GLFW_KEY_F3)) {
		setVerticalSynchronization(!isVerticalSynchronizationEnabled());
	}

	std::string windowTitleWithFPS = "FPS: "
		+ std::to_string(getFPS()) +
		", VSync: " + (isVerticalSynchronizationEnabled() ? "On" : "Off") + " (Press F3 to toggle)";
	glfwSetWindowTitle(getWindow(), windowTitleWithFPS.c_str());
}

void MainWindow::releaseScene()
{
	NULLPTR_CHECK_DELETE(mpCheckboard);
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
