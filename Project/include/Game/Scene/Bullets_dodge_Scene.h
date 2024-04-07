#pragma once

#ifndef TESTQUADTREECOLLISIONSCENE_H_
#define TESTQUADTREECOLLISIONSCENE_H_

#include <Game/Scene/SceneBase.h>
#include <Game/Object/dodge_bullet/dodge_bullet.h>
#include <Game/Score/Score_dodge.h>

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

	void bullet_position_create(int num, vec2& start, vec2& end);
	bool isIntersecting2D(vec2 rayOrigin, vec2 rayDirection);
	void bullet_create();

private:
	shared_ptr<Sprite> mpBackGround;
	
	unique_ptr<Score_dodge> mpScore;
	float mScore = 0.0f;

	shared_ptr<Player> mpPlayer;

	shared_ptr<QuadTree> mpQuadTree;
	vector<shared_ptr<Sprite>> mSprites;
	
	random_device mRandomDevice1, mRandomDevice2, mRandomDevice3, mRandomDevice4;
	unique_ptr<dodge_bullet> mpBullet[2000];
	const int mBulletMaxCount = 2000;
	queue<int> mBulletEndIndexQueue;
	const double mBulletCreateTime = 2.0f;
	double mBulletCreateTimer = 0.0f;
	int mBullet_count = 0;
	vec2 boxMin, boxMax;
	vec4 front_vec, back_vec, right_vec, left_vec;

};

#endif // !TESTQUADTREECOLLISIONSCENE_H_

