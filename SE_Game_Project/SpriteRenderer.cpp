#include "SpriteRenderer.h"

const char* SPRITE_VERTEX_SHADER = { 
	"#version 330 core \n"
	"layout (location = 0) in vec3 vertexPosition; \n"
	"layout (location = 1) in vec4 vertexColor;	\n"
	"out vec4 fragmentColor; \n"
	"uniform mat4 cameraMatrix; \n"
	"void main() \n"
	"{ \n"
		"gl_Position = vec4(vertexPosition.x, vertexPosition.y, 0.0, 1.0); \n"
		"fragmentColor = vertexColor; \n"
	"} \n" 
};

const char* SPRITE_FRAGMENT_SHADER = {
	"#version 330 core\n"
	"in vec4 fragmentColor;\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{ \n"
		"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); \n"
	"} \n"};


SpriteRenderer::SpriteRenderer()
{
}

void SpriteRenderer::on_init(Camera& camera)
{
	m_camera = camera;

	// TODO: Shader initialization code here!
	m_shader.init(SPRITE_VERTEX_SHADER, SPRITE_FRAGMENT_SHADER);
	m_shader.add_attributes({ "vertexPosition", "vertexColor" });
	m_shader.link_shaders();




	// Two triangles make up a square. Colors default to 255
	testVertices[0].position = glm::vec2(-1.0, 1.0);
	testVertices[1].position = glm::vec2(-1.0, -1.0);
	testVertices[2].position = glm::vec2(1.0, -1.0);
	testVertices[3].position = glm::vec2(1.0, -1.0);
	testVertices[4].position = glm::vec2(1.0, 1.0);
	testVertices[5].position = glm::vec2(-1.0, 1.0);

	glGenVertexArrays(1, &m_playerVAO);
	glBindVertexArray(m_playerVAO);

	glGenBuffers(1, &m_playerVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_playerVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	//glGenBuffers(1, &m_playerVBO);

	//glBindVertexArray(m_playerVAO);

	//glBindBuffer(GL_ARRAY_BUFFER, m_playerVBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(testVertices), testVertices, GL_STATIC_DRAW);

	//glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 
	//	sizeof(testVertices), (void*)offsetof(Vertex, position));
	//glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, 
	//	sizeof(testVertices), (void*)offsetof(Vertex, color));
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);
}

void SpriteRenderer::on_update()
{

}

void SpriteRenderer::on_render(glm::vec2 playerPosition)
{
	// Bind shader
	m_shader.bind();


	//glUniformMatrix4fv(m_shader.get_uniform("cameraMatrix"),
	//	1, GL_FALSE, &(m_camera.m_cameraMatrix[0][0]));
	//m_shader.set_uniform("particleTexture", 0);
	//m_shader.set_uniform("cameraRight", cameraRight);
	//m_shader.set_uniform("cameraUp", cameraUp);

	//int numActive = 0;
	//for (int i = 0; i < m_batches[index]->m_maxAmount; i++) {
	//	Particle2& p = m_batches[index]->m_particles[i];
	//	if (p.life > 0.0f) {
	//		m_batches[index]->particle_buffer_to_render[numActive].m_pointCoord = glm::vec4(p.poos, p.sizeA);
	//		m_batches[index]->particle_buffer_to_render[numActive].m_color = p.color;
	//		numActive++;
	//	}
	//}

	glBindVertexArray(m_playerVAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(0);


	// Bind texture
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, m_batches[index]->m_glTexture.id);
	//glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, numActive);
	//glBindTexture(GL_TEXTURE_2D, 0);

	// Unbind shader
	m_shader.unbind();
}
