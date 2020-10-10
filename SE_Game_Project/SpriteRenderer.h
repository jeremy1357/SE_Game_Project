// Created by Jeremy Bowler
// October 10 19, 2020

#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "Shader.h"
#include "Vertex.h"
#include "Camera.h"

class SpriteRenderer
{
public:
	SpriteRenderer();
	void on_init(Camera& camera);
	void on_update();
	void on_render(glm::vec2 playerPosition);

private:
	float vertices[9] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};
	Camera m_camera;
	Vertex testVertices[6];
	Shader m_shader;
	GLuint m_playerVBO;
	GLuint m_playerVAO;
};

