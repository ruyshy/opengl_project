#include <pch.h>

#include <OpenGL/Sprite/Sprite.h>
#include <OpenGL/Texture2D/Texture2D.h>
#include <OpenGL/Shader/Shader.h>

#include <OpenGL/VertexBuffer2D/VertexBuffer2D.h>
#include<OpenGL/Transform2D/Transform2D.h>

Sprite::Sprite(shared_ptr<Shader> shader, const char* filename)
	: mpShader(shader), ObjectBase(0, "Sprite"), mScreenX(0), mScreenY(0), mScreenW(800), mScreenH(600), mLastX(0), mLastY(0)
{
	mpTextured = make_shared<Texture2D>(TextureSystem::Generate(filename));
	mpVertexBufferObject = make_shared<VertexBufferObject2D>(VertexBufferSystem2D::Generate());
	mpTransform = make_shared<Transform2D>();
}

Sprite::Sprite(shared_ptr<Shader> shader, const char* filename, float x, float y, float xx, float yy)
	: mpShader(shader), ObjectBase(0, "Sprite"), mScreenX(x), mScreenY(y), mScreenW(xx), mScreenH(yy)
{
	mpTextured = make_shared<Texture2D>(TextureSystem::Generate(filename));
	mpVertexBufferObject = make_shared<VertexBufferObject2D>(VertexBufferSystem2D::Generate());
	mpTransform = make_shared<Transform2D>();
}

Sprite::~Sprite()
{
	TextureSystem::Delete(*mpTextured);
	VertexBufferSystem2D::Delete(*mpVertexBufferObject);
}

void Sprite::Draw()
{
	if (!mVisible)return;

	mpShader->use();
	mpShader->setFloat("zDepth", mZDepth);
	mpShader->setMat4("model_matrx", mpTransform->Get());
	mpTextured->use();
	mpVertexBufferObject->Draw();
}

bool Sprite::checkCollision(shared_ptr<Sprite> other)
{
	return GetPosition().x < other->GetPosition().x + other->GetScale().x && GetPosition().x + GetScale().x > other->GetPosition().x &&
		GetPosition().y < other->GetPosition().y + other->GetScale().y && GetPosition().y + GetScale().y > other->GetPosition().y;
}

bool Sprite::hasMoved()
{
	return GetPosition().x != mLastX || GetPosition().y != mLastY;
}

bool Sprite::hasScreen()
{
	return
		GetPosition().x + GetScale().x >= (mScreenX + GetScale().x) &&
		GetPosition().x <= (mScreenW - GetScale().x) &&
		GetPosition().y + GetScale().y >= (mScreenY + GetScale().y) &&
		GetPosition().y <= (mScreenH - GetScale().y);
}

bool Sprite::hasScreen(float width, float height)
{
	return 
		GetPosition().x + GetScale().x >= (width + GetScale().x) &&
		GetPosition().x <= (width - GetScale().x) &&
		GetPosition().y + GetScale().y >= (height + GetScale().y) &&
		GetPosition().y <= (height - GetScale().y);
}

void Sprite::update()
{
	mLastX = GetPosition().x;
	mLastY = GetPosition().y;
}

shared_ptr<Transform2D> Sprite::GetTransform() { return mpTransform; }
bool Sprite::GetVisible() { return mVisible; }
vec2 Sprite::GetPosition() { return mpTransform->GetPosition(); }
vec2 Sprite::GetCenter() { return mpTransform->GetCenter(); }
vec2 Sprite::GetScale() { return mpTransform->GetScale(); }
mat4 Sprite::GetMatrix() { return mpTransform->Get(); }
float Sprite::GetAngle() { return mpTransform->GetAngle(); }
bool Sprite::GetFlipX() { return mpTransform->GetFlipX(); }
bool Sprite::GetFlipY() { return mpTransform->GetFlipY(); }
vec4 Sprite::GetScreen() { return vec4(mScreenX, mScreenY, mScreenW, mScreenH); }


//Set
void Sprite::SetTransform(Transform2D transform)
{
	mpTransform->SetPosition(transform.GetPosition());
	mpTransform->SetScale(transform.GetScale());
	mpTransform->SetAngle(transform.GetAngle());
	mpTransform->SetFlipX(transform.GetFlipX());
	mpTransform->SetFlipY(transform.GetFlipY());
}
void Sprite::SetVisible(bool visible) { mVisible = visible; }
void Sprite::SetPosition(vec2 position) { mpTransform->SetPosition(position); }
void Sprite::SetPosition(float x, float y) { mpTransform->SetPosition(vec2(x, y)); }
void Sprite::SetDepth(float value) { mZDepth = value; }
void Sprite::SetScale(vec2 scale) { mpTransform->SetScale(scale); }
void Sprite::SetScale(float x, float y) { mpTransform->SetScale(vec2(x, y)); }
void Sprite::SetAngle(float angle) { mpTransform->SetAngle(angle); }
void Sprite::SetFlipX(bool flip) { mpTransform->SetFlipX(flip); }
void Sprite::SetFlipY(bool flip) { mpTransform->SetFlipY(flip); }
