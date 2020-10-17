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
	GLuint numSquares = 0;
	GLuint indexOffset = 0;
};

struct LightBatch {
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	GLuint textureID;
	GLuint numSquares = 0;
	GLuint indexOffset = 0;

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
	void add_static_sprite_to_batch(
		const glm::vec2& position,
		const GLuint& textureID);
	void add_light_to_batch(
		const glm::vec2& position, 
		const glm::vec2& dimensions,
		const ColorRGBA32& color);
private:
	std::string m_resourceDirectory = "";
	std::vector<SpriteBatch> m_dynamicBatches;
	std::vector<SpriteBatch> m_staticBatches;
	LightBatch m_lightBatch;

	bool m_doesStaticBatchesNeedRender = true;
	Camera* m_camera;
	TextureCache* m_textureCache;
	Shader m_shader;
	Shader m_lightShader;

	GLuint m_dynamicVBO;
	GLuint m_dynamicVAO;
	GLuint m_dynamicEBO;
	GLuint m_staticVBO;
	GLuint m_staticVAO;
	GLuint m_staticEBO;
	GLuint m_lightVBO;
	GLuint m_lightVAO;
	GLuint m_lightEBO;

	// IF YOU CHANGE THIS, MUST CHANGE THE ONE IN THE LevelManager!
	const glm::vec2 tileDimensions = glm::vec2(75.0f, 75.0f);
	// These are constant. Dont change
	const glm::vec2 tlUV = glm::vec2(0.0, 1.0);
	const glm::vec2 trUV = glm::vec2(1.0, 1.0);
	const glm::vec2 blUV = glm::vec2(0.0, 0.0);
	const glm::vec2 brUV = glm::vec2(1.0, 0.0);
};

