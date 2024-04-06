#pragma once

#ifndef ENEMY_H_
#define ENEMY_H_

#include <Game/Object/ObjectBase.h>

class Enemy : public ObjectBase
{
public:
	Enemy(shared_ptr<Shader> shader, const char* filePath);
	virtual ~Enemy();

	shared_ptr<Sprite> GetSprite();

protected:
	shared_ptr<Sprite> mpSprite;
	float mHp, mSpeed;


};

#endif
