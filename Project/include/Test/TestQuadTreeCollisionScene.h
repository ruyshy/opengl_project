#pragma once

#ifndef TESTQUADTREECOLLISIONSCENE_H_
#define TESTQUADTREECOLLISIONSCENE_H_

#include <Game/Scene/SceneBase.h>

class QuadTree;
class Player;
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
	void checkCollisions(shared_ptr<QuadTree> quadtree);

private:
	shared_ptr<Player> mpPlayer;
	shared_ptr<Sprite> mpSprite;

	shared_ptr<QuadTree> mpQuadTree;
	vector<shared_ptr<Sprite>> mSprites;
	


};

#endif // !TESTQUADTREECOLLISIONSCENE_H_

