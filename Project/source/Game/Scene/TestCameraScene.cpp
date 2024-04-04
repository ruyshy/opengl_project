#include <pch.h>
#include <Game/Scene/TestCameraScene.h>
#include <Game/Game.h>

#include <OpenGL/Camera/Camera.h>
#include <OpenGL/Sprite/Sprite.h>
#include <OpenGL/Transform2D/Transform2D.h>
#include <OpenGL/Quad/Quad.h>

#include <Game/Object/Character/Character.h>

void TestCameraScene::initializeScene()
{
	mpCharacter = make_shared<Character>(mpGame->GetTextureShader(), ".\\Image\\character.png");
	vec2 center = vec2((*mpGame->GetWindow()->GetWidth() / 2) - 50, (*mpGame->GetWindow()->GetHeight() / 2) + 100);
	mpCharacter->GetSprite()->SetPosition(center);

	vec2 ground_position(vec2(0, *mpGame->GetWindow()->GetHeight() - 50));
	mpGround = make_shared<Quad>(mpGame->GetNormalShader(), ground_position, *mpGame->GetWindow()->GetWidth(), 100);
	mpGround->SetColor(0, 0.5, 0, 1);
}

void TestCameraScene::renderScene()
{
	mpCharacter->Draw();
	mpGround->Draw();
}

void TestCameraScene::updateScene()
{
	mpCharacter->Movement([this](int key) {return mpGame->GetWindow()->keyPressed(key); }, mpGame->GetWindow()->getTimeDelta());
	
	vec3 point = vec3(
		mpCharacter->GetSprite()->GetPosition().x - (*mpGame->GetWindow()->GetWidth() / 2) + 50,
		mpCharacter->GetSprite()->GetPosition().y - (*mpGame->GetWindow()->GetHeight() / 2) - 100,
		0.0f);

	mpGame->GetCamera()->SetPosition(point);

}

void TestCameraScene::releaseScene()
{

}
