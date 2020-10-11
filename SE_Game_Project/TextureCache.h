// Created by Jeremy Bowler
// October 10, 2020
#pragma once
#include <unordered_map>
#include <string>
#include <GL/glew.h>

struct Texture {
	GLuint textureID;
};

class TextureCache
{
public:
	TextureCache();
	~TextureCache();

	GLuint get_texture_id(std::string texturePath);

private:
	bool load_texture_from_PNG(std::string texturePath, GLuint& textureID);
	std::unordered_map<std::string, Texture> m_textureCache;

};

