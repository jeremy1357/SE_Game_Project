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
	std::vector<VertexSimple> vertices;
	std::vector<GLuint> indices;
	GLuint textureID;
};

class SpriteRenderer
{
public:
	SpriteRenderer();
	void on_init(Camera& camera, TextureCache& textureCache, const std::string& projectDirectory);
	void on_update();
	void on_render();
	void add_sprite_to_batch(
		const glm::vec2& position, 
		const glm::vec2& dimensions,
		const std::string& textureName,
		const float& dirAngle);
	void add_sprite_to_batch(
		const glm::vec2& position, 
		const glm::vec2& dimensions,
		const GLuint& textureID,
		const float& dirAngle);
	void add_sprite_to_batch(
		const glm::vec2& position,
		const GLuint& textureID);

private:
	std::string m_resourceDirectory = "";
	std::vector<SpriteBatch> m_spriteBatches;
	Camera* m_camera;
	TextureCache* m_textureCache;
	Shader m_shader;
	GLuint m_playerVBO;
	GLuint m_playerVAO;
	GLuint m_spriteEBO;
	const glm::vec2 tileDimensions = glm::vec2(50.0f, 50.0f);
	// These are constant. Dont change
	const glm::vec2 tlUV = glm::vec2(0.0, 1.0);
	const glm::vec2 trUV = glm::vec2(1.0, 1.0);
	const glm::vec2 blUV = glm::vec2(0.0, 0.0);
	const glm::vec2 brUV = glm::vec2(1.0, 0.0);


};

