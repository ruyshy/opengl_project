#pragma once

#ifndef LINE_H_

using namespace glm;
class Shader;

class Line {
private:
	Line();
public:
	Line(vec2 start, vec2 end, float _width = 1.0f);
	Line(vector<vec2> _points, float _width = 1.0f);
	~Line();

	void SetColor(vec3 color);
	vec3 GetColor();

	void Draw();
	void Draw(mat4 _projection_matrix);

private:
	unsigned int VAO;  //vertex array object
	unsigned int VBO;  // vertex buffer object
	unsigned int EBO;	// Element Buffer Object
	unsigned int* indices;

	unsigned int points_size;
	unsigned int indices_size;

private:
	Shader* mpShader = nullptr;

	vector<vec2> points;
	mat4 projection_matrix;
	mat4 model_matrx;
	vec3 Color;
	float Width;

};


#endif // !LINE_H_
