#pragma once

#ifndef DODGE_BULLET_H_
#define DODGE_BULLET_H_

class dodge_bullet
{
protected:
	dodge_bullet() = delete;
public:
	dodge_bullet(shared_ptr<Shader> shader, const char* filePath, vec2 start, vec2 end, float speed);
	virtual ~dodge_bullet();

	void reload(vec2 start, vec2 end, float speed);

	float distance(const vec2& a, const vec2& b);
	bool isNearDestination(const vec2& current, const vec2& destination, float threshold);
	bool EndGoal();
	
	void SetState(bool state);
	bool GetState();
	
	void Movement(double delta_time);
	void Draw();

	shared_ptr<Sprite> GetSprite();

private:
	shared_ptr<Sprite> mpSprite;
	vec2 mStart, mEnd, mDirection;
	float mSpeed = 100.0f;
	bool mState;
};

#endif // !DODGE_BULLET_H_
