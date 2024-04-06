#pragma once

#ifndef TESTQUADTREECOLLISIONSCENE_H_
#define TESTQUADTREECOLLISIONSCENE_H_

#include <Game/Scene/SceneBase.h>

class QuadTree;
class Player;
class Quad;

class Bullets_dodge_Scene : public SceneBase
{
public:
	SceneCreator(Bullets_dodge_Scene);

	void initializeScene() override;
	void renderScene()override;
	void updateScene()override;
	void releaseScene()override;

private:
	void checkCollisions(shared_ptr<QuadTree> quadtree);
	void checkPlayerCollsions(shared_ptr<QuadTree> quadtree);

private:
	shared_ptr<Sprite> mpBackGround;
	shared_ptr<Player> mpPlayer;

	shared_ptr<QuadTree> mpQuadTree;
	vector<shared_ptr<Sprite>> mSprites;
	


};

#endif // !TESTQUADTREECOLLISIONSCENE_H_

