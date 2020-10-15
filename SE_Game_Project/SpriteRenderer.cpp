#include "SpriteRenderer.h"

const char* SPRITE_VERTEX_SHADER = { 
	"#version 330 core \n"
	"layout (location = 0) in vec2 vertexPosition; \n"
	"layout (location = 1) in vec2 vertexUV;	\n"
	"out vec2 fragmentUV; \n"
	"uniform mat4 cameraMatrix; \n"
	"void main() \n"
	"{ \n"
		"gl_Position.xy = (cameraMatrix * vec4(vertexPosition, 0.0f, 1.0f)).xy;\n"
		"gl_Position.z = 0.0f;\n"
		"gl_Position.w = 1.0f;\n"
		"fragmentUV = vertexUV; \n"
	"} \n" 
};

const char* SPRITE_FRAGMENT_SHADER = {
	"#version 330 core\n"
	"in vec2 fragmentUV;\n"
	"out vec4 FragColor;\n"
	"uniform sampler2D tex;\n"
	"void main()\n"
	"{ \n"
		"FragColor = texture(tex, fragmentUV); \n"
	"} \n"};


SpriteRenderer::SpriteRenderer()
{
}

void SpriteRenderer::on_init(Camera& camera, TextureCache& textureCache, const std::string& projectDirectory)
{
	m_camera = &camera;
	m_textureCache = &textureCache;
	m_resourceDirectory = projectDirectory + "Resources\\Textures\\";


	m_shader.init(SPRITE_VERTEX_SHADER, SPRITE_FRAGMENT_SHADER);
	m_shader.add_attributes({ "vertexPosition", "vertexUV" });
	m_shader.link_shaders();

	glGenVertexArrays(1, &m_playerVAO);
	glGenBuffers(1, &m_playerVBO);
	glBindVertexArray(m_playerVAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_playerVBO);


	// Each vertex object contains three attributes.
	// 1) Position -> glm::vec2
	// 2) ColorRGBA32 -> uint8_t rgba[4]
	// 3) UV -> glm::vec2
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
		sizeof(VertexSimple), (void*)offsetof(VertexSimple, position));
	//glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE,
	//	sizeof(Vertex), (void*)offsetof(Vertex, color));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
		sizeof(VertexSimple), (void*)offsetof(VertexSimple, uv));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// Element buffer to store vertex indices
	glGenBuffers(1, &m_spriteEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_spriteEBO);
	glBindVertexArray(0);

}

void SpriteRenderer::on_update()
{

}

void SpriteRenderer::on_render()
{
	std::vector<VertexSimple> allVertices;
	std::vector<GLuint> textureIDs;
	std::vector<GLuint> offsetStarts;
	std::vector<GLuint> offsetSizes;


	for (size_t i = 0; i < m_spriteBatches.size(); i++) {
		GLuint start = 0;
		if (i != 0) {
			for (size_t x = 0; x < offsetStarts.size(); x++) {
				start += m_spriteBatches[x].vertices.size() * 6;
			}
		}
		allVertices.insert(allVertices.end(), m_spriteBatches[i].vertices.begin(), m_spriteBatches[i].vertices.end());
		offsetStarts.push_back(start);
		offsetSizes.push_back(m_spriteBatches[i].vertices.size() * 6);

		textureIDs.push_back(m_spriteBatches[i].textureID);
	}


	std::vector<GLuint> allIndices;
	// Resize now for performance
	allIndices.resize(allVertices.size() * 6);

	GLuint startingIndex = 0;

	for (size_t i = 0; i < allVertices.size(); i+= 6) {
		// Store vertex indices 
		allIndices[i] = startingIndex;
		allIndices[i + 1] = (startingIndex + 1);
		allIndices[i + 2] = (startingIndex + 2);
		allIndices[i + 3] = (startingIndex + 2);
		allIndices[i + 4] = (startingIndex + 1);
		allIndices[i + 5] = (startingIndex + 3);
		startingIndex += 4;
	}
	glBindVertexArray(m_playerVAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_playerVBO);
	GLuint vertexDataSize = allVertices.size() * sizeof(VertexSimple);
	glBufferData(GL_ARRAY_BUFFER, vertexDataSize, &allVertices[0], GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	GLuint elementDataSize = allIndices.size() * sizeof(GLuint);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_spriteEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementDataSize, &allIndices[0], GL_DYNAMIC_DRAW);

	glBindVertexArray(0);

	//// Bind shader
	//m_shader.bind();
	//m_shader.set_uniform("tex", 0);

	//glm::mat4 projectionMatrix = m_camera->m_cameraMatrix;
	//m_shader.set_uniform("cameraMatrix", projectionMatrix);
	//glBindVertexArray(m_playerVAO);

	//for (int i = 0; i < m_spriteBatches.size(); i++) {

	//	glActiveTexture(GL_TEXTURE0);
	//	glBindTexture(GL_TEXTURE_2D, m_spriteBatches[i].textureID);

	//	glBindBuffer(GL_ARRAY_BUFFER, m_playerVBO);
	//	GLuint vertexDataSize = m_spriteBatches[i].vertices.size() * sizeof(VertexSimple);
	//	glBufferData(GL_ARRAY_BUFFER, vertexDataSize, &m_spriteBatches[i].vertices[0], GL_DYNAMIC_DRAW);
	//	glBindBuffer(GL_ARRAY_BUFFER, 0);


	//	GLuint elementDataSize = m_spriteBatches[i].indices.size() * sizeof(GLuint);
	//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_spriteEBO);
	//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementDataSize, &m_spriteBatches[i].indices[0], GL_DYNAMIC_DRAW);

	//	glDrawElements(GL_TRIANGLES, m_spriteBatches[i].indices.size(), GL_UNSIGNED_INT, 0);
	//	glBindTexture(GL_TEXTURE_2D, 0);

	//}
	//glBindVertexArray(0);

	//m_shader.unbind();

	//// At the end of each render. Clear batches
	//m_spriteBatches.clear();


		// Bind shader
	m_shader.bind();
	m_shader.set_uniform("tex", 0);

	glm::mat4 projectionMatrix = m_camera->m_cameraMatrix;
	m_shader.set_uniform("cameraMatrix", projectionMatrix);
	glBindVertexArray(m_playerVAO);
	glActiveTexture(GL_TEXTURE0);

	for (size_t i = 0; i < offsetStarts.size(); i++) {
		glBindTexture(GL_TEXTURE_2D, m_spriteBatches[i].textureID);
		glDrawRangeElements(GL_TRIANGLES, offsetStarts[i], allIndices.size(), offsetSizes[i], GL_UNSIGNED_INT, 0);

	}
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindVertexArray(0);

	m_shader.unbind();

	// At the end of each render. Clear batches
	m_spriteBatches.clear();
}

void SpriteRenderer::add_sprite_to_batch(
	const glm::vec2& position,
	const glm::vec2& dimensions,
	const std::string& textureName,
	const float& dirAngle)
{
	GLuint textureID = m_textureCache->get_texture_id(m_resourceDirectory + textureName);
	add_sprite_to_batch(position, dimensions, textureID, dirAngle);


}

void SpriteRenderer::add_sprite_to_batch(
	const glm::vec2& position,
	const glm::vec2& dimensions,
	const GLuint& textureID,
	const float& dirAngle)
{
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
	// These are constant. Dont change
	glm::vec2 tlUV = glm::vec2(0.0, 1.0);
	glm::vec2 trUV = glm::vec2(1.0, 1.0);
	glm::vec2 blUV = glm::vec2(0.0, 0.0);
	glm::vec2 brUV = glm::vec2(1.0, 0.0);

	// Add in the new vertices. Rotate each vertex
	it->vertices.push_back(VertexSimple(tl, tlUV));
	it->vertices.back().rotate(dirAngle, position);
	it->vertices.push_back(VertexSimple(tr, trUV));
	it->vertices.back().rotate(dirAngle, position);
	it->vertices.push_back(VertexSimple(bl, blUV));
	it->vertices.back().rotate(dirAngle, position);
	it->vertices.push_back(VertexSimple(br, brUV));
	it->vertices.back().rotate(dirAngle, position);



}

void SpriteRenderer::add_sprite_to_batch(
	const glm::vec2& position, 
	const glm::vec2& dimensions, 
	const GLuint& textureID)
{
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
	glm::vec2 tr = position;
	glm::vec2 bl = position;
	glm::vec2 br = position;

	tl.x -= dimensions.x;
	tl.y += dimensions.y;

	tr.x += dimensions.x;
	tr.y += dimensions.y;

	bl.x -= dimensions.x;
	bl.y -= dimensions.y;

	br.x += dimensions.x;
	br.y -= dimensions.y;

	uint32_t index = it->vertices.size();
	it->vertices.resize(index + 4);
	// Add in the new vertices. Rotate each vertex
	it->vertices[index++] = VertexSimple(tl, tlUV);
	it->vertices[index++] = VertexSimple(tr, trUV);
	it->vertices[index++] = VertexSimple(bl, blUV);
	it->vertices[index] = VertexSimple(br, brUV);

}
