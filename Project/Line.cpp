#include "pch.h"
#include "Line.h"

#include "Shader.h"
#include "ResourceManager.h"

#include "shader_resource.h"

Line::Line()
{
	mpShader = new Shader(
		ResourceManager::GetResourceString(IDR_NORMAL_VS, Resource::SHADER),
		ResourceManager::GetResourceString(IDR_NORMAL_FS, Resource::SHADER)
	);

	points = vector<vec2>();

	projection_matrix = mat4(1.0f);
	model_matrx = mat4(1.0f);

	Width = 1.0f;
	Color = vec3(1, 0, 0);

}

Line::Line(vec2 start, vec2 end, float _width) : Line()
{
	vec2 direction = normalize(end - start);
	Width = _width;

	vec2 right = vec2(direction.y, -direction.x);
	vec2 left = vec2(-direction.y, direction.x);
	right.x = right.x * Width;
	right.y = right.y * Width;
	left.x = left.x * Width;
	left.y = left.y * Width;

	points.push_back((start + left));
	points.push_back((start + right));
	points.push_back((end + left));
	points.push_back((end + right));

	points_size = points.size();
	indices_size = 6;
	indices = new unsigned int[6];
	indices[0] = 0;	indices[1] = 1;
	indices[2] = 2;	indices[3] = 2;
	indices[4] = 1;	indices[5] = 3;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, points_size * sizeof(points), points.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size * sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, NULL);
	glEnableVertexAttribArray(0);
}

Line::Line(vector<vec2> _points, float _width) : Line()
{
	int size = _points.size();
	Width = _width;

	for (int x = 0; x < (size - 1); x+=2)
	{
		vec2 curr = _points[x];
		vec2 next = _points[x + (size_t)1];

		vec2 direction = normalize(next - curr);

		vec2 right = vec2(direction.y, -direction.x);
		vec2 left = vec2(-direction.y, direction.x);
		right.x = right.x * Width;
		right.y = right.y * Width;
		left.x = left.x * Width;
		left.y = left.y * Width;

		points.push_back((curr + left));
		points.push_back((curr + right));
		points.push_back((next + left));
		points.push_back((next + right));
	}
	points_size = points.size();
	indices_size = 6 * (points_size / 4);

	unsigned int sequence = 0;
	indices = new unsigned int[indices_size];
	for (int x = 0; x < indices_size; x += 6)
	{
		if (x > indices_size)
			break;

		indices[x]			= sequence;
		indices[x + 1]	= sequence + 1;
		indices[x + 2]	= sequence + 2;
		indices[x + 3]	= sequence + 2;
		indices[x + 4]	= sequence + 1;
		indices[x + 5]	= sequence + 3;

		sequence += 4;
	}

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, points_size * sizeof(points), points.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size * sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, NULL);
	glEnableVertexAttribArray(0);

}

Line::~Line() 
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	if (mpShader != nullptr)
	{
		delete mpShader;
		mpShader = nullptr;
	}
	if (indices != nullptr)
	{
		delete[] indices;
		indices = nullptr;
	}
}

void Line::SetColor(vec3 color)
{
	Color = color;
}

vec3 Line::GetColor()
{
	return Color;
}

void Line::Draw()
{
	mpShader->use();
	mpShader->setMat4("projection", projection_matrix);
	//mpShader->setMat4("model_matrx", model_matrx);
	mpShader->setVec3("color", Color);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices_size, GL_UNSIGNED_INT, 0);

}

void Line::Draw(mat4 _projection_matrix)
{
	projection_matrix = _projection_matrix;

	mpShader->use();
	mpShader->setMat4("projection", projection_matrix);
	//mpShader->setMat4("model_matrx", model_matrx);
	mpShader->setVec3("color", Color);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices_size, GL_UNSIGNED_INT, 0);

}
