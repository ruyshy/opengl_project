#pragma once

#ifndef CHARACTER_H_
#define CHARACTER_H_

class Player
{
protected:
	Player() = delete;
public:
	Player(shared_ptr<Shader> shader, const char* filePath);
	virtual ~Player();

public:
	void Movement(std::function<bool(int)> keyFunction, double delta_time);
	shared_ptr<Sprite> GetSprite();

	void SetSpeed(float speed);

	void Draw();

private:
	shared_ptr<Sprite> mpSprite;
	float mHp = 10.0f, mSpeed = 100.0f;

};

#endif // !CHARACTER_H_
