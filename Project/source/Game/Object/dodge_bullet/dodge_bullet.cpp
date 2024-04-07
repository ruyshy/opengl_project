#include <pch.h>
#include <Game/Object/dodge_bullet/dodge_bullet.h>

dodge_bullet::dodge_bullet(shared_ptr<Shader> shader, const char* filePath, vec2 start, vec2 end, float speed)
{
	mpSprite = make_shared<Sprite>(shader, filePath);
	mpSprite->SetPosition(0, 0);
	mpSprite->SetScale(10, 10);
	mpSprite->SetID(1);
	mpSprite->SetName("dodge_bullet");
	mpSprite->SetDepth(0.01);

	this->start = start;
	this->end = end;
	direction = end - start;
	float len = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	direction.x /= len;
	direction.y /= len;

	mpSprite->SetPosition(start);

	mSpeed = speed;
}

dodge_bullet::~dodge_bullet()
{
}

void dodge_bullet::Movement(double delta_time)
{
	double speed = mSpeed * delta_time;
	vec2 movement = mpSprite->GetPosition();
	mpSprite->SetPosition(vec2(movement + vec2(direction.x * speed, direction.y * speed)));
}

void dodge_bullet::Draw()
{
	mpSprite->Draw();
}

shared_ptr<Sprite> dodge_bullet::GetSprite() { return mpSprite; }
