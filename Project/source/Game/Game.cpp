#include <pch.h>
#include <Game/Game.h>

#include <OpenGL/Camera/Camera.h>
#include <OpenGL/Sprite/Sprite.h>
#include <Game/Scene/SceneBase.h>

#include <OpenGL/VertexBuffer2D/VertexBuffer2D.h>

#include <Manager/ResourceManager.h>
#include <rc/shader_resource.h>

Game::Game(MainWindow* mainWindow)
{
	mpMainWindow = mainWindow;

}

Game::~Game()
{
	VertexBufferSystem2D::Delete(*mpCheckboard);
}

void Game::initialize()
{
	mpCheckboardShader = make_unique<Shader>(
		ResourceManager::GetResourceString(IDR_SHADER_CHECKBOARD_VS, Resource::SHADER),
		ResourceManager::GetResourceString(IDR_SHADER_CHECKBOARD_FS, Resource::SHADER));
	mpTextureShader = make_shared<Shader>(
		ResourceManager::GetResourceString(IDR_SHADER_TEXTURED_VS, Resource::SHADER),
		ResourceManager::GetResourceString(IDR_SHADER_TEXTURED_FS, Resource::SHADER));
	mpNormalShader = make_shared<Shader>(
		ResourceManager::GetResourceString(IDR_NORMAL_VS, Resource::SHADER),
		ResourceManager::GetResourceString(IDR_NORMAL_FS, Resource::SHADER));
	mpCheckboard = make_unique<VertexBufferObject2D>(VertexBufferSystem2D::Generate());

	mpCamera = make_unique<Camera>(mpTextureShader, mpMainWindow->GetWidth(), mpMainWindow->GetHeight());

	//mpCharacter = make_shared<Character>(mpTextureShader, "C:\\Project\\opengl_project\\Project\\Image\\character.png");
}

void Game::Render() const
{
	mpCamera->Update();
	mpCheckboardShader->use();
	mpCheckboardShader->setMat4("projection", mpMainWindow->getOrthoProjectionMatrix());
	mpCheckboardShader->setMat4("model_matrx", scale(mat4(1), vec3(mpMainWindow->getScreenWidth(), mpMainWindow->getScreenHeight(), 1)));
	mpCheckboardShader->setVec2("resolution", vec2(mpMainWindow->getScreenWidth(), mpMainWindow->getScreenHeight()));
	mpCheckboard->Draw();

}

void Game::Update() const
{
	//mpCamera->Movement([this](int key) {return this->keyPressed(key); }, getTimeDelta());
	//mpCharacter->Movement([this](int key) {return this->keyPressed(key); }, getTimeDelta());
}
