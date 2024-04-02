#pragma once

#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <Game/Object/GObjectBase.h>

class Character : public GObjectBase
{
protected:
	Character() = delete;
public:
	Character(shared_ptr<Shader> shader, const char* filePath);
	virtual ~Character();

	void Movement(std::function<bool(int)> keyFunction, double delta_time);

public:
	void Draw();

private:
	shared_ptr<Sprite> mpSprite;
	double mSpeed = 100.0f;

};

#endif // !CHARACTER_H_
