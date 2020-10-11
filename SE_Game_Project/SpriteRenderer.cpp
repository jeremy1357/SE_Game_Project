#include "SpriteRenderer.h"

const char* SPRITE_VERTEX_SHADER = { 
	"#version 330 core \n"
	"layout (location = 0) in vec2 vertexPosition; \n"
	"layout (location = 1) in vec4 vertexColor;	\n"
	"layout (location = 2) in vec2 vertexUV;	\n"
	"out vec4 fragmentColor; \n"
	"out vec2 fragmentUV; \n"
	"uniform mat4 cameraMatrix; \n"
	"void main() \n"
	"{ \n"
		"gl_Position.xy = (cameraMatrix * vec4(vertexPosition, 0.0f, 1.0f)).xy;\n"
		"gl_Position.z = 0.0f;\n"
		"gl_Position.w = 1.0f;\n"
		"fragmentColor = vertexColor; \n"
		"fragmentUV = vertexUV; \n"
	"} \n" 
};

const char* SPRITE_FRAGMENT_SHADER = {
	"#version 330 core\n"
	"in vec4 fragmentColor;\n"
	"in vec2 fragmentUV;\n"
	"out vec4 FragColor;\n"
	"uniform sampler2D tex;\n"
	"void main()\n"
	"{ \n"
		"FragColor = texture(tex, fragmentUV) * fragmentColor; \n"
	"} \n"};


SpriteRenderer::SpriteRenderer()
{
}

void SpriteRenderer::on_init(Camera& camera, TextureCache& textureCache)
{
	m_camera = &camera;
	m_textureCache = &textureCache;

	// TODO: Shader initialization code here!
	m_shader.init(SPRITE_VERTEX_SHADER, SPRITE_FRAGMENT_SHADER);
	m_shader.add_attributes({ "vertexPosition", "vertexColor", "vertexUV" });
	m_shader.link_shaders();

	glGenVertexArrays(1, &m_playerVAO);
	glGenBuffers(1, &m_playerVBO);

	glBindVertexArray(m_playerVAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_playerVBO);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), (void*)offsetof(Vertex, position));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE,
		sizeof(Vertex), (void*)offsetof(Vertex, color));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), (void*)offsetof(Vertex, uv));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	// Element buffer
	glGenBuffers(1, &m_spriteEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_spriteEBO);


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

void SpriteRenderer::on_render()
{


	m_shader.set_uniform("tex", 0);
	//m_shader.set_uniform("cameraRight", cameraRight);
	//m_shader.set_uniform("cameraUp", cameraUp);

	// Bind shader
	m_shader.bind();
	glm::mat4 projectionMatrix = m_camera->m_cameraMatrix;
	m_shader.set_uniform("cameraMatrix", projectionMatrix);

	for (int i = 0; i < m_spriteBatches.size(); i++) {
		glBindVertexArray(m_playerVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_spriteBatches[i].textureID);

		glBindBuffer(GL_ARRAY_BUFFER, m_playerVBO);
		GLuint vertexDataSize = m_spriteBatches[i].vertices.size() * sizeof(Vertex);
		glBufferData(GL_ARRAY_BUFFER, vertexDataSize, &m_spriteBatches[i].vertices[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);


		GLuint elementDataSize = m_spriteBatches[i].indices.size() * sizeof(GLuint);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_spriteEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementDataSize, &m_spriteBatches[i].indices[0], GL_STATIC_DRAW);

		glDrawElements(GL_TRIANGLES, m_spriteBatches[i].indices.size(), GL_UNSIGNED_INT, 0);
		glBindTexture(GL_TEXTURE_2D, 0);

		glBindVertexArray(0);

	}

	m_shader.unbind();


	// Bind texture


	// Unbind shader

	// At the end of each render. Clear batches
	m_spriteBatches.clear();
}

void SpriteRenderer::add_sprite_to_batch(glm::vec2 position, 
	glm::vec2 dimensions, std::string textureName)
{
	GLuint textureID = m_textureCache->get_texture_id(textureName);
	int batchIndex = -1;
	// Check to see if any stored batches matches this sprites texture ID
	// If not, create a new batch
	for (int i = 0; i < m_spriteBatches.size(); i++) {
		if (m_spriteBatches[i].textureID == textureID) {
			batchIndex = i;
			break;
		}
	}
	std::vector<SpriteBatch>::iterator it;
	if (batchIndex == -1) {
		m_spriteBatches.push_back(SpriteBatch());
		it = m_spriteBatches.end() - 1;
		it->textureID = textureID;
	}
	else {
		it = m_spriteBatches.begin() + batchIndex;
	}
	glm::vec2 tl = position;
	tl.x -= dimensions.x;
	tl.y += dimensions.y;
	glm::vec2 tr = position;
	tr.x += dimensions.x;
	tr.y += dimensions.y;
	glm::vec2 bl = position;
	bl.x -= dimensions.x;
	bl.y -= dimensions.y;
	glm::vec2 br = position;
	br.x += dimensions.x;
	br.y -= dimensions.y;
	glm::vec2 tlUV = glm::vec2(0.0, 1.0);
	glm::vec2 trUV = glm::vec2(1.0, 1.0);
	glm::vec2 blUV = glm::vec2(0.0, 0.0);
	glm::vec2 brUV = glm::vec2(1.0, 0.0);

	// Add in the new vertices and indices
	it->vertices.push_back(Vertex(tl, tlUV));
	it->vertices.push_back(Vertex(tr, trUV));
	it->vertices.push_back(Vertex(bl, blUV));
	it->vertices.push_back(Vertex(br, brUV));
	GLuint startingIndex = 0;
	if (it->indices.size() != 0) {
		startingIndex = it->indices.back() + 1;
	}

	it->indices.push_back(startingIndex);
	it->indices.push_back(startingIndex + 1);
	it->indices.push_back(startingIndex + 2);
	it->indices.push_back(startingIndex + 2);
	it->indices.push_back(startingIndex + 1);
	it->indices.push_back(startingIndex + 3);


}
