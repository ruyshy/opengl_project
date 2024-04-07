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

	void game_over_initialize();

private:
	void checkCollisions(shared_ptr<QuadTree> quadtree);
	void checkPlayerCollsions(shared_ptr<QuadTree> quadtree);

	int randomInt(int min, int max);
	float randomFloat(float min, float max);

	void bullet_position_create(int num, vec2& start, vec2& end);
	bool isIntersecting2D(vec2 rayOrigin, vec2 rayDirection);
	void bullet_create();

private:
	bool mGameStart = false, mGameEnd = false, mLose = false;
	int mLastIndex = -1;
	unique_ptr<TextRendering> mpGameStartText;

	const string mStartTextContexts = "Press the space bar or enter to start the game.";
	const string mEndTextContexts = "Game Over. Press the space bar or enter to re start the game.";
	shared_ptr<Sprite> mpBackGround;
	unique_ptr<Score_dodge> mpScore;
	float mScore = 0.0f;

	shared_ptr<Player> mpPlayer;

	shared_ptr<QuadTree> mpQuadTree;
	vector<shared_ptr<Sprite>> mSprites;
	
	std::mt19937 gen;
	unique_ptr<dodge_bullet> mpBullet[1000];
	const int mBulletMaxCount = 1000;
	queue<int> mBulletEndIndexQueue;
	const double mBulletCreateTime = 2.0f;
	double mBulletCreateTimer = 100.0f;
	int mBullet_count = 0;
	vec2 boxMin, boxMax;
	float mBulletMinX, mBulletMaxX;
	float mBulletMinY, mBulletMaxY;

};

#endif // !TESTQUADTREECOLLISIONSCENE_H_

