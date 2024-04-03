#pragma once

#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <Game/Object/ObjectBase.h>

class Character : public ObjectBase
{
protected:
	Character() = delete;
public:
	Character(shared_ptr<Shader> shader, const char* filePath);
	virtual ~Character();

public:
	void Movement(std::function<bool(int)> keyFunction, double delta_time);
	shared_ptr<Sprite> GetSprite();
	QuadtreeNode::Rect getBounds() const;


	void Draw();

private:
	shared_ptr<Sprite> mpSprite;
	double mSpeed = 100.0f;

};

#endif // !CHARACTER_H_
