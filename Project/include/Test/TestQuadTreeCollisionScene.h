#pragma once

#ifndef TESTQUADTREECOLLISIONSCENE_H_
#define TESTQUADTREECOLLISIONSCENE_H_
#include <Game/Scene/SceneBase.h>

class QuadTree;
class Character;
class Quad;

class TestQuadTreeCollisionScene : public SceneBase
{
public:
	SceneCreator(TestQuadTreeCollisionScene);

	void initializeScene() override;
	void renderScene()override;
	void updateScene()override;
	void releaseScene()override;

private:
	void checkCollisions();

private:
	shared_ptr<Character> mpCharacter;
	shared_ptr<Sprite> mpSprite;

	shared_ptr<QuadTree> mpQuadTree;
	vector<shared_ptr<Sprite>> mSprites;
	


};

#endif // !TESTQUADTREECOLLISIONSCENE_H_

