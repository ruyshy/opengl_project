#include <pch.h>
#include <Game/Object/Player/Player.h>
#include <OpenGL/Sprite/Sprite.h>

Player::Player(shared_ptr<Shader> shader, const char* filePath)
{
	mpSprite = make_shared<Sprite>(shader, filePath);
	mpSprite->SetPosition(0,0);
	mpSprite->SetScale(100, 100);
	mpSprite->SetID(0);
	mpSprite->SetName("Player");
}

Player::~Player()
{

}

void Player::Movement(std::function<bool(int)> keyFunction, double delta_time)
{
	const double correction = 0.75f;
	double speed = mSpeed * delta_time;
	vec4 screen = mpSprite->GetScreen();
	vec2 movement = mpSprite->GetPosition();
	vec2 scale = mpSprite->GetScale();

	if (keyFunction(GLFW_KEY_W) && movement.y + scale.y >= (screen.y + (scale.y * correction)))
	{
		movement = movement + vec2(0, -speed);
		mpSprite->SetPosition(movement);
	}
	if (keyFunction(GLFW_KEY_S) && movement.y <= (screen.w - (scale.y * correction)))
	{
		movement = movement + vec2(0, speed);
		mpSprite->SetPosition(movement);
	}
	if (keyFunction(GLFW_KEY_A) && movement.x + scale.x >= (screen.x + (scale.x * correction)))
	{
		movement = movement + vec2(-speed, 0);
		mpSprite->SetPosition(movement);
	}
	if (keyFunction(GLFW_KEY_D) && movement.x <= (screen.z - (scale.x * correction)))
	{
		movement = movement + vec2(speed, 0);
		mpSprite->SetPosition(movement);
	}
}

shared_ptr<Sprite> Player::GetSprite() { return mpSprite; }

void Player::SetSpeed(float speed) { mSpeed = speed; }

void Player::Draw()
{
	mpSprite->Draw();
}
