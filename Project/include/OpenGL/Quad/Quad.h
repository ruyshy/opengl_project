#pragma once

#ifndef QUAD_H_
#define QUAD_H_

class Quad
{
public:
	Quad() = delete;
	Quad(shared_ptr<Shader> shader, vec2 position, double size);
	Quad(shared_ptr<Shader> shader, vec2 position, double width, double height);
	~Quad();

	void SetColor(vec4 color);
	void SetColor(float r, float g, float b, float a);
	vec4 GetColor();

	void Draw();
	void DrawOutline();

	Transform2DHeaderMacro();

private:
	unsigned int VAO;  //vertex array object
	unsigned int VBO;  // vertex buffer object
	unsigned int EBO;	// Element Buffer Object
private:
	shared_ptr<Shader> mpShader = nullptr;
	Transform2D* mpTransfrom = nullptr;

	vector<vec2> mPoints;
	mat4 model_matrx;
	vec4 mColor;
	double Width;

};

#endif // !QUAD_H_
