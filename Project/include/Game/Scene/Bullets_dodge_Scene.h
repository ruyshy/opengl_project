#pragma once

#ifndef TESTQUADTREECOLLISIONSCENE_H_
#define TESTQUADTREECOLLISIONSCENE_H_

#include <Game/Scene/SceneBase.h>
#include <Game/Object/dodge_bullet/dodge_bullet.h>

class QuadTree;
class Player;

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

	void bullet_create();

private:
	shared_ptr<Sprite> mpBackGround;
	shared_ptr<Player> mpPlayer;

	shared_ptr<QuadTree> mpQuadTree;
	vector<shared_ptr<Sprite>> mSprites;
	
	random_device mRandomDevice;
	unique_ptr<dodge_bullet> mpBullet[2000];
	const int mBulletMaxCount = 2000;
	const double mBulletCreateTime = 2.0f;
	double mBulletCreateTimer = 0.0f;
	int mBullet_count = 0;


};

#endif // !TESTQUADTREECOLLISIONSCENE_H_

