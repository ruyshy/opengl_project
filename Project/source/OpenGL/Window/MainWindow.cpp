#include <pch.h>
#include <OpenGL/Window/MainWindow.h>

#include <OpenGL/Shader/Shader.h>
#include <OpenGL/Sprite/Sprite.h>
#include <OpenGL/Quad/Quad.h>

#include <Manager/ResourceManager.h>
#include <rc/shader_resource.h>


#include <OpenGL/Sprite/Sprite.h>
#include <OpenGL/Camera/Camera.h>
#include <Game/Object/Character/Character.h>

MainWindow::MainWindow()
{
	mpProjectionMatrix = new mat4(1.0f);
	mpWidth = make_shared<int>(0);
	mpHeight = make_shared<int>(0);

}

MainWindow::~MainWindow()
{
	NULLPTR_CHECK_DELETE(mpProjectionMatrix);
}

void MainWindow::initializeScene()
{
	glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	mpCheckboardShader = make_unique<Shader>(
		ResourceManager::GetResourceString(IDR_SHADER_CHECKBOARD_VS, Resource::SHADER),
		ResourceManager::GetResourceString(IDR_SHADER_CHECKBOARD_FS, Resource::SHADER));
	mpTextureShader = make_shared<Shader>(
		ResourceManager::GetResourceString(IDR_SHADER_TEXTURED_VS, Resource::SHADER),
		ResourceManager::GetResourceString(IDR_SHADER_TEXTURED_FS, Resource::SHADER));

	mpCamera = make_unique<Camera>(mpTextureShader, mpWidth, mpHeight);

	mpCharacter = make_shared<Character>(mpTextureShader, "C:\\Project\\opengl_project\\Project\\Image\\character.png");

	mpCheckboard = make_unique<VertexBufferObject2D>(VertexBufferSystem2D::Generate());
}

void MainWindow::renderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	mpCamera->Update();

	mpCheckboardShader->use();
	mpCheckboardShader->setMat4("projection", getOrthoProjectionMatrix());
	mpCheckboardShader->setMat4("model_matrx", scale(mat4(1), vec3(getScreenWidth(), getScreenHeight(), 1)));
	mpCheckboardShader->setVec2("resolution", vec2(getScreenWidth(), getScreenHeight()));
	mpCheckboard->draw();

	mpTextureShader->use();
	mpCharacter->Draw();

}

void MainWindow::updateScene()
{
	
	if (keyPressedOnce(GLFW_KEY_F3)) {
		setVerticalSynchronization(!isVerticalSynchronizationEnabled());
	}
	mpCamera->Key_Update([this](int key) {return this->keyPressed(key); }, getTimeDelta());
	//mpCharacter->Movement([this](int key) {return this->keyPressed(key); }, getTimeDelta());

	std::string windowTitleWithFPS = "FPS: "
		+ std::to_string(getFPS()) +
		", VSync: " + (isVerticalSynchronizationEnabled() ? "On" : "Off") + " (Press F3 to toggle)";
	glfwSetWindowTitle(getWindow(), windowTitleWithFPS.c_str());
}

void MainWindow::releaseScene()
{
	VertexBufferSystem2D::Delete(*mpCheckboard);
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
