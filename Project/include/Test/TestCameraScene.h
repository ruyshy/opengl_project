#pragma once

#ifndef TESTCAMERASCENE_H_
#define TESTCAMERASCENE_H_
#include <Game/Scene/SceneBase.h>

class Player;
class Quad;

class TestCameraScene : public SceneBase
{
public:
	SceneCreator(TestCameraScene);

	void initializeScene() override;
	void renderScene()override;
	void updateScene()override;
	void releaseScene()override;

private:
	shared_ptr<Player> mpCharacter;
	shared_ptr<Quad> mpGround;
};


#endif // !TESTCAMERASCENE_H_
