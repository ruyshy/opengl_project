#include <pch.h>
#include <Game/Object/Character/Character.h>
#include <OpenGL/Sprite/Sprite.h>

Character::Character(shared_ptr<Shader> shader, const char* filePath) : ObjectBase(0, "Character")
{
	mpSprite = make_shared<Sprite>(shader, filePath);
	mpSprite->SetPosition(0,0);
	mpSprite->SetScale(100, 100);

}

Character::~Character()
{

}

void Character::Movement(std::function<bool(int)> keyFunction, double delta_time)
{

	if (keyFunction(GLFW_KEY_W))
	{
		double speed = mSpeed * delta_time;
		vec2 movement = mpSprite->GetPosition() + vec2(0, -speed);
		mpSprite->SetPosition(movement);
	}
	if (keyFunction(GLFW_KEY_S))
	{
		double speed = mSpeed * delta_time;
		vec2 movement = mpSprite->GetPosition() + vec2(0, speed);
		mpSprite->SetPosition(movement);
	}
	if (keyFunction(GLFW_KEY_A))
	{
		double speed = mSpeed * delta_time;
		vec2 movement = mpSprite->GetPosition() + vec2(-speed, 0);
		mpSprite->SetPosition(movement);
	}
	if (keyFunction(GLFW_KEY_D))
	{
		double speed = mSpeed * delta_time;
		vec2 movement = mpSprite->GetPosition() + vec2(speed, 0);
		mpSprite->SetPosition(movement);
	}
}

void Character::Draw()
{
	mpSprite->Draw();
}
