// Created by Jeremy Bowler
// October 10, 2020
#pragma once
#include <map>
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

	GLuint get_texture_id(const std::string& texturePath, bool clamp = true);

private:
	bool load_texture_from_PNG(std::string texturePath, GLuint& textureID, bool clamp = true);
	std::map<std::string, Texture> m_textureCache;

};

