#include <pch.h>
#include <Game/Object/Enemy/EnemyTrooper1.h>

Enemy::Enemy(shared_ptr<Shader> shader, const char* filePath) : ObjectBase(1, "Enemy")
{

}

Enemy::~Enemy()
{

}

shared_ptr<Sprite> Enemy::GetSprite() { return mpSprite; }
