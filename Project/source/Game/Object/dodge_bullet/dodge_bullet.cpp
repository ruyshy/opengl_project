#include <pch.h>
#include <Game/Object/dodge_bullet/dodge_bullet.h>

dodge_bullet::dodge_bullet(shared_ptr<Shader> shader, const char* filePath, vec2 direction, float speed)
{
	mpSprite = make_shared<Sprite>(shader, filePath);
	mpSprite->SetPosition(0, 0);
	mpSprite->SetScale(10, 10);
	mpSprite->SetID(1);
	mpSprite->SetName("dodge_bullet");

	mDirection_vector = direction;
	mSpeed = speed;
}

dodge_bullet::~dodge_bullet()
{
}

void dodge_bullet::Movement(double delta_time)
{
	mpSprite->SetDepth(0.01);
	mpSprite->SetPosition(vec2(mpSprite->GetPosition() + vec2(mDirection_vector.x * delta_time, mDirection_vector.y * delta_time)));
}

void dodge_bullet::Draw()
{
	mpSprite->Draw();
}

shared_ptr<Sprite> dodge_bullet::GetSprite() { return mpSprite; }
