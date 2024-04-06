#include <pch.h>
#include <Game/Object/dodge_bullet/dodge_bullet.h>

dodge_bullet::dodge_bullet(shared_ptr<Shader> shader, const char* filePath, vec2 direction, float speed)
{
	mpSprite = make_shared<Sprite>(shader, filePath);
	mpSprite->SetPosition(0, 0);
	mpSprite->SetScale(100, 100);
	mpSprite->SetID(1);
	mpSprite->SetName("dodge_bullet");

	mDirection_vector = direction;
	mSpeed = speed;
}

dodge_bullet::~dodge_bullet()
{
}

void dodge_bullet::Movement()
{
	mpSprite->SetDepth(0.01);
	mpSprite->SetPosition(vec2(mpSprite->GetPosition() + mDirection_vector));
	mpSprite->Draw();
}
