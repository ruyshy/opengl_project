#pragma once

#ifndef TEXTURE_H_
#define TEXTURE_H_

class Texture2D
{
public:
	int width;
	int height;
	unsigned int ID;

	void use();
};

class TextureSystem
{
public:

	static Texture2D Generate(const char* filename);
	static Texture2D Generate(string image);
	static void Delete(Texture2D& obj);


};

#endif // !TEXTURE_H_