#pragma once

#ifndef TRANSFORM_MACRO_H_
#define TRANSFORM_MACRO_H_

#pragma region Transform2D

class Transform2D;

#define Transform2DHeaderMacro()																			\
void SetTransform(Transform2D transform);																	\
mat4 GetTransform();																								\
void SetScale(double x, double y);																				\
void SetScale(vec2 mScale);																						\
vec2 GetScale();																									\
void SetPosition(double x, double y);																			\
void SetPosition(vec2 mPosition);																				\
vec2 GetPosition();																									\
void SetAngle(float angle);																						\
float GetAngle();																									\
void SetFlipX(bool flipX);																							\
bool GetFlipX();																										\
void SetFlipY(bool flipY);																							\
bool GetFlipY();																										\

#define Transform2DNormalCppMacro(class_name, transform_name)									\
void class_name::SetTransform(Transform2D transform) { transform_name = transform; }			\
mat4 class_name::GetTransform() { return transform_name.Get(); }										\
void class_name::SetScale(double x, double y) { transform_name. = vec2(x, y); }						\
void class_name::SetScale(vec2 mScale) { transform_name.mScale = mScale; }							\
vec2 class_name::GetScale() { return transform_name.mScale; }												\
void class_name::SetPosition(double x, double y) { transform_name.mPosition = vec2(x, y); }		\
void class_name::SetPosition(vec2 mPosition) { transform_name.mPosition = mPosition; }			\
vec2 class_name::GetPosition() { return transform_name.mPosition; }										\
void class_name::SetAngle(float angle) { transform_name.angle = angle; }								\
float class_name::GetAngle() { return transform_name.angle; }												\
void class_name::SetFlipX(bool flipX) { transform_name.flipX = flipX; }									\
bool class_name::GetFlipX() { return transform_name.flipX; }												\
void class_name::SetFlipY(bool flipY) { transform_name.flipY = flipY; }									\
bool class_name::GetFlipY() { return transform_name.flipY; }													\

#define Transform2DPointerCppMacro(class_name, transform_name)									\
void class_name::SetTransform(Transform2D transform) { *transform_name = transform; }			\
mat4 class_name::GetTransform() { return transform_name->Get(); }										\
void class_name::SetScale(double x, double y) { transform_name->SetScale(vec2(x, y)); }			\
void class_name::SetScale(vec2 mScale) { transform_name->SetScale(mScale); }						\
vec2 class_name::GetScale() { return transform_name->GetScale(); }										\
void class_name::SetPosition(double x, double y) { transform_name->SetPosition(vec2(x, y)); }		\
void class_name::SetPosition(vec2 mPosition) { transform_name->SetPosition(mPosition); }			\
vec2 class_name::GetPosition() { return transform_name->GetPosition(); }								\
void class_name::SetAngle(float angle) { transform_name->SetAngle(angle); }							\
float class_name::GetAngle() { return transform_name->GetAngle(); }										\
void class_name::SetFlipX(bool flipX) { transform_name->SetFlipX(flipX); }								\
bool class_name::GetFlipX() { return transform_name->GetFlipX(); }										\
void class_name::SetFlipY(bool flipY) { transform_name->SetFlipY(flipY); }								\
bool class_name::GetFlipY() { return transform_name->GetFlipY(); }										\

#pragma endregion


#endif // !TRANSFORM_MACRO_H_
