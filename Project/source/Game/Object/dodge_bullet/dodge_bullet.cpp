#include <pch.h>
#include <Game/Object/dodge_bullet/dodge_bullet.h>

dodge_bullet::dodge_bullet(shared_ptr<Shader> shader, const char* filePath, vec2 start, vec2 end, float speed)
{
	mpSprite = make_shared<Sprite>(shader, filePath);
	mpSprite->SetScale(10, 10);
	mpSprite->SetID(1);
	mpSprite->SetName("dodge_bullet");
	mpSprite->SetDepth(0.01);

	this->mStart = start;
	mpSprite->SetPosition(start);
	this->mEnd = end;
	mDirection = end - start;
	float len = std::sqrt(mDirection.x * mDirection.x + mDirection.y * mDirection.y);
	mDirection.x /= len;
	mDirection.y /= len;


	mSpeed = speed;
	mState = false;
}

dodge_bullet::~dodge_bullet()
{
}

void dodge_bullet::reload(vec2 start, vec2 end, float speed)
{
	this->mStart = start;
	this->mEnd = end;
	mDirection = end - start;
	float len = std::sqrt(mDirection.x * mDirection.x + mDirection.y * mDirection.y);
	mDirection.x /= len;
	mDirection.y /= len;
	mpSprite->SetPosition(0, 0);

	mpSprite->SetPosition(start);

	mSpeed = speed;
	mState = false;
}

float dodge_bullet::distance(const vec2& a, const vec2& b)
{
	return std::sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

bool dodge_bullet::isNearDestination(const vec2& current, const vec2& destination, float threshold)
{
	return distance(current, destination) < threshold;
}

bool dodge_bullet::EndGoal()
{
	if (isNearDestination(mpSprite->GetPosition(), mEnd, 1.0f)) 
		return true;
	return false;
}

void dodge_bullet::SetState(bool state) { mState = state; }
bool dodge_bullet::GetState() { return mState; }

void dodge_bullet::Movement(double delta_time)
{
	double speed = mSpeed * delta_time;
	vec2 movement = mpSprite->GetPosition();
	mpSprite->SetPosition(vec2(movement + vec2(mDirection.x * speed, mDirection.y * speed)));
}

void dodge_bullet::Draw()
{
	mpSprite->Draw();
}

shared_ptr<Sprite> dodge_bullet::GetSprite() { return mpSprite; }
