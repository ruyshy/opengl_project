#include <pch.h>
#include <OpenGL/Window/MainWindow.h>

#include <OpenGL/Shader/Shader.h>
#include <OpenGL/Sprite/Sprite.h>
#include <OpenGL/Quad/Quad.h>

#include <Manager/ResourceManager.h>
#include <rc/shader_resource.h>

#include <glm/gtc/matrix_transform.hpp>
#include <utill/stb_image.h>

#include <OpenGL/Model3D/Mesh.h>
#include <OpenGL/Model3D/Model3D.h>
#include <OpenGL/Sprite/Sprite.h>
#include <OpenGL/Camera/Camera.h>

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

	mpCheckboard = make_unique<Shader>(
		ResourceManager::GetResourceString(IDR_SHADER_CHECKBOARD_VS, Resource::SHADER),
		ResourceManager::GetResourceString(IDR_SHADER_CHECKBOARD_FS, Resource::SHADER));
	//mpModelLoadingShader = make_unique<Shader>(
	//	ResourceManager::GetResourceString(IDR_SHADER_MODEL_LOADING_VS, Resource::SHADER),
	//	ResourceManager::GetResourceString(IDR_SHADER_MODEL_LOADING_FS, Resource::SHADER));
	mpTextureShader = new Shader(
		ResourceManager::GetResourceString(IDR_SHADER_TEXTURED_VS, Resource::SHADER),
		ResourceManager::GetResourceString(IDR_SHADER_TEXTURED_FS, Resource::SHADER));

	mpCamera = make_unique<Camera>(0, 0);
	mpSprite = new Sprite(mpTextureShader, "C:\\Project\\Jaehyeok\\opengl_project\\backpack\\test.png");
	mpSprite->SetPosition(vec2(0, 0));
	mpSprite->SetScale(vec2(200, 200));

	rect = VertexBufferSystem2D::Generate();
	//mpModel3D = new Model3D("C:\\Project\\opengl_project\\backpack\\backpack.obj");
}

void MainWindow::renderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	mpCamera->Update_Viewport(getScreenWidth(), getScreenHeight());
	mpCheckboard->use();
	mpCheckboard->setMat4("projection", mpCamera->Get_Projection());
	mpCheckboard->setMat4("model_matrx", glm::scale(glm::mat4(1), glm::vec3(getScreenWidth(), getScreenHeight(), 1)));
	mpCheckboard->setVec2("resolution", glm::vec2(getScreenWidth(), getScreenHeight()));
	rect.draw();

	mpTextureShader->use();
	mpTextureShader->setMat4("projection", getOrthoProjectionMatrix());
	mpSprite->Draw();
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
	NULLPTR_CHECK_DELETE(mpTextureShader);
	NULLPTR_CHECK_DELETE(mpSprite);
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
