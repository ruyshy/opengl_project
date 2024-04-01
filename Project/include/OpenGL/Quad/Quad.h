#pragma once

#ifndef QUAD_H_
#define QUAD_H_

class Quad
{
public:
	Quad();
	Quad(vec2 position, double width = 1.0f);
	~Quad();

	void SetColor(vec4 color);
	void SetColor(float r, float g, float b, float a);
	vec4 GetColor();

	void Draw();
	void Draw(mat4 _projection_matrix);

	Transform2DHeaderMacro();

private:
	unsigned int VAO;  //vertex array object
	unsigned int VBO;  // vertex buffer object
	unsigned int EBO;	// Element Buffer Object
private:
	Shader* mpShader = nullptr;
	Transform2D* mpTransfrom = nullptr;

	vector<vec2> points;
	mat4 projection_matrix;
	mat4 model_matrx;
	vec4 Color;
	float Width;

};

#endif // !QUAD_H_
