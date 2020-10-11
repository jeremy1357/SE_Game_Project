// Created by Jeremy Bowler
// October 10, 2020

#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "Shader.h"
#include "Vertex.h"
#include "Camera.h"
#include "TextureCache.h"
#include <string>

// POD Plain-Old-Data
struct SpriteBatch {
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	GLuint textureID;
};

class SpriteRenderer
{
public:
	SpriteRenderer();
	void on_init(Camera& camera, TextureCache& textureCache);
	void on_update();
	void on_render();
	void add_sprite_to_batch(glm::vec2 position, glm::vec2 dimensions, std::string textureName);

private:
	std::vector<SpriteBatch> m_spriteBatches;

	Camera* m_camera;
	TextureCache* m_textureCache;

	//Vertex testVertices[4];
	//GLuint m_indices[6];

	Shader m_shader;
	GLuint m_playerVBO;
	GLuint m_playerVAO;
	GLuint m_spriteEBO;
};

