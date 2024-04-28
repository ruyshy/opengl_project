#include <pch.h>
#include <Test/Test3DScene.h>
#include <Game/Game.h>
#include <OpenGL/Model/Model.h>

void Test3DScene::initializeScene()
{
	mpModel = make_shared<Model>("C:\\Project\\opengl_project\\Project\\backpack\\backpack.obj");
	mpSprite = make_shared<Sprite>(mpGame->GetTextureShader(), ".\\Image\\character.png");
	mpSprite->SetScale(100, 100);
	mpSprite->SetPosition(0, 0);

}

void Test3DScene::renderScene()
{
	mpModel->Draw(*mpGame->GetModelShader());
	mpSprite->Draw();
}

void Test3DScene::updateScene()
{
	mpGame->GetCamera()->Movement([this](int key) {return mpGame->GetWindow()->keyPressed(key); }, mpGame->GetWindow()->getTimeDelta());
}

void Test3DScene::releaseScene()
{

}
