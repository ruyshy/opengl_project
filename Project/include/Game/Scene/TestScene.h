#pragma once

#ifndef TESTSCENE_H_
#define TESTSCENE_H_
#include <Game/Scene/SceneBase.h>

class Character;
class Quad;

class TestScene : public SceneBase
{
public:
	SceneCreator(TestScene);

	void initializeScene() override;
	void renderScene()override;
	void updateScene()override;
	void releaseScene()override;

private:
	void checkCollisions(QuadtreeNode& rootNode, const Sprite& target, std::vector<std::shared_ptr<Sprite>>& potentialCollisions);

private:
	shared_ptr<Character> mpCharacter;
	shared_ptr<Sprite> mpSprite;

	shared_ptr<QuadtreeNode> mRootNode;
	vector<shared_ptr<Sprite>> mSprites;
	


};

#endif // !TESTSCENE_H_

