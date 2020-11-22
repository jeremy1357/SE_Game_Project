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
		"FragColor = texture(tex, -fragmentUV); \n"
	"} \n"};



const char* LIGHT_VERTEX_SHADER = {
	"#version 330 core \n"
	"layout (location = 0) in vec2 vertexPosition; \n"
	"layout (location = 1) in vec2 vertexUV;	\n"
	"layout (location = 2) in vec4 vertexColor;	\n"
	"out vec2 fragmentUV; \n"
	"out vec4 fragmentColor; \n"
	"uniform mat4 cameraMatrix; \n"
	"void main() \n"
	"{ \n"
		"gl_Position.xy = (cameraMatrix * vec4(vertexPosition, 0.0f, 1.0f)).xy;\n"
		"gl_Position.z = 0.0f;\n"
		"gl_Position.w = 1.0f;\n"
		"fragmentUV = vertexUV; \n"
		"fragmentColor = vertexColor; \n"
	"} \n"
};

const char* LIGHT_FRAGMENT_SHADER = {
	"#version 330 core\n"
	"in vec2 fragmentUV;\n"
	"in vec4 fragmentColor;\n"
	"out vec4 FragColor;\n"
	"uniform sampler2D tex;\n"
	"void main()\n"
	"{ \n"
		"FragColor = texture(tex, -fragmentUV) * fragmentColor; \n"
	"} \n" };



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
	m_lightShader.init(LIGHT_VERTEX_SHADER, LIGHT_FRAGMENT_SHADER);
	m_lightShader.add_attributes({ "vertexPosition", "vertexUV", "vertexColor" });
	m_lightShader.link_shaders();

	m_lightBatch.textureID = m_textureCache->get_texture_id(m_resourceDirectory + "light.png");
	m_particleBatch.textureID = m_textureCache->get_texture_id(m_resourceDirectory + "particle.png");

	glGenVertexArrays(1, &m_staticVAO);
	glGenBuffers(1, &m_staticVBO);
	glGenBuffers(1, &m_staticEBO);
	glBindVertexArray(m_staticVAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_staticVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_staticEBO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
		sizeof(VertexSimple), (void*)offsetof(VertexSimple, position));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
		sizeof(VertexSimple), (void*)offsetof(VertexSimple, uv));
	glBindVertexArray(0);

	glGenVertexArrays(1, &m_dynamicVAO);
	glGenBuffers(1, &m_dynamicVBO);
	glGenBuffers(1, &m_dynamicEBO);
	glBindVertexArray(m_dynamicVAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_dynamicVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_dynamicEBO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
		sizeof(VertexSimple), (void*)offsetof(VertexSimple, position));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
		sizeof(VertexSimple), (void*)offsetof(VertexSimple, uv));
	glBindVertexArray(0);

	glGenVertexArrays(1, &m_lightVAO);
	glGenBuffers(1, &m_lightVBO);
	glGenBuffers(1, &m_lightEBO);
	glBindVertexArray(m_lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_lightVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_lightEBO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), (void*)offsetof(Vertex, position));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), (void*)offsetof(Vertex, uv));
	glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE,
		sizeof(Vertex), (void*)offsetof(Vertex, color));
	glBindVertexArray(0);


	glGenVertexArrays(1, &m_particleVAO);
	glGenBuffers(1, &m_particleVBO);
	glGenBuffers(1, &m_particleEBO);
	glBindVertexArray(m_particleVAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_particleVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_particleEBO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), (void*)offsetof(Vertex, position));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), (void*)offsetof(Vertex, uv));
	glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE,
		sizeof(Vertex), (void*)offsetof(Vertex, color));
	glBindVertexArray(0);


}

void SpriteRenderer::on_update()
{

}

void SpriteRenderer::on_render()
{
	m_shader.bind();
	m_shader.set_uniform("tex", 0);
	glm::mat4 projectionMatrix = m_camera->m_cameraMatrix;
	m_shader.set_uniform("cameraMatrix", projectionMatrix);

	if (m_doesStaticBatchesNeedRender) {
		m_doesStaticBatchesNeedRender = false;
		std::vector<GLuint> staticIndices;
		std::vector<VertexSimple> staticVertices;
		int xx = 0;
		GLuint startIndex = 0;

		for (auto& batch : m_staticBatches) {
			staticVertices.insert(std::end(staticVertices), std::begin(batch.vertices), std::end(batch.vertices));
			GLuint offsetIndex = 0;
			if (xx != 0) {
				for (int j = 0; j < xx; j++) {
					offsetIndex += m_staticBatches[j].numSquares * 6;
				}
			}
			xx += 1;
			batch.indexOffset = offsetIndex;
			for (size_t x = 0; x < batch.numSquares; x++) {
				// Store vertex indices 
				staticIndices.push_back(startIndex);
				staticIndices.push_back(startIndex + 1);
				staticIndices.push_back(startIndex + 2);
				staticIndices.push_back(startIndex + 2);
				staticIndices.push_back(startIndex + 1);
				staticIndices.push_back(startIndex + 3);
				startIndex += 4;
			}
		}

		glBindVertexArray(m_staticVAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_staticVBO);
		GLuint vertexDataSize = staticVertices.size() * sizeof(VertexSimple);
		glBufferData(GL_ARRAY_BUFFER, vertexDataSize, nullptr, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertexDataSize, staticVertices.data());
		GLuint elementDataSize = staticIndices.size() * sizeof(GLuint);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_staticEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementDataSize, nullptr, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, elementDataSize, staticIndices.data());
		glBindVertexArray(0);
		staticIndices.clear();
		staticVertices.clear();
	}

	glBindVertexArray(m_staticVAO);
	glActiveTexture(GL_TEXTURE0);
	for (auto& batch : m_staticBatches) {
		glBindTexture(GL_TEXTURE_2D, batch.textureID);
		glDrawElements(GL_TRIANGLES, batch.numSquares * 6, GL_UNSIGNED_INT, (void*)(batch.indexOffset * sizeof(GLuint)));
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);





	glBindVertexArray(m_dynamicVAO);
	for (auto& batch : m_dynamicBatches) {
		batch.indices.resize(batch.numSquares * 6);
		GLuint startIndex = 0;
		for (size_t x = 0; x < batch.indices.size(); x += 6) {
			// Store vertex indices 
			batch.indices[x] = startIndex;
			batch.indices[x + 1] = (startIndex + 1);
			batch.indices[x + 2] = (startIndex + 2);
			batch.indices[x + 3] = (startIndex + 2);
			batch.indices[x + 4] = (startIndex + 1);
			batch.indices[x + 5] = (startIndex + 3);
			startIndex += 4;
		}
	}
	for (auto& batch : m_dynamicBatches) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, batch.textureID);
		glBindBuffer(GL_ARRAY_BUFFER, m_dynamicVBO);
		GLuint vertexDataSize = batch.vertices.size() * sizeof(VertexSimple);
		glBufferData(GL_ARRAY_BUFFER, vertexDataSize, nullptr, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertexDataSize, batch.vertices.data());
		GLuint elementDataSize = batch.indices.size() * sizeof(GLuint);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_dynamicEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementDataSize, nullptr, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, elementDataSize, batch.indices.data());
		glDrawElements(GL_TRIANGLES, batch.indices.size(), GL_UNSIGNED_INT, 0);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	m_shader.unbind();
	// At the end of each render. Clear batches
	m_dynamicBatches.clear();
	




	std::vector<GLuint> lightIndices;
	lightIndices.resize(m_lightBatch.numSquares * 6);
	GLuint lightIndex = 0;
	for (size_t x = 0; x < lightIndices.size(); x += 6) {
		// Store vertex indices 
		lightIndices[x] = lightIndex;
		lightIndices[x + 1] = (lightIndex + 1);
		lightIndices[x + 2] = (lightIndex + 2);
		lightIndices[x + 3] = (lightIndex + 2);
		lightIndices[x + 4] = (lightIndex + 1);
		lightIndices[x + 5] = (lightIndex + 3);
		lightIndex += 4;
	}
	std::vector<GLuint> particleIndices;
	particleIndices.resize(m_particleBatch.numSquares * 6);
	GLuint particleIndex = 0;
	for (size_t x = 0; x < particleIndices.size(); x += 6) {
		// Store vertex indices 
		particleIndices[x] = particleIndex;
		particleIndices[x + 1] = (particleIndex + 1);
		particleIndices[x + 2] = (particleIndex + 2);
		particleIndices[x + 3] = (particleIndex + 2);
		particleIndices[x + 4] = (particleIndex + 1);
		particleIndices[x + 5] = (particleIndex + 3);
		particleIndex += 4;
	}

	m_lightShader.bind();
	m_lightShader.set_uniform("tex", 0);
	m_lightShader.set_uniform("cameraMatrix", projectionMatrix);
	glBindVertexArray(m_lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_lightVBO);
	GLuint vertexDataSize = m_lightBatch.vertices.size() * sizeof(Vertex);
	glBufferData(GL_ARRAY_BUFFER, vertexDataSize, nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertexDataSize, m_lightBatch.vertices.data());
	GLuint elementDataSize = lightIndices.size() * sizeof(GLuint);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_lightEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementDataSize, nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, elementDataSize, lightIndices.data());
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_lightBatch.textureID);
	glDrawElements(GL_TRIANGLES, lightIndices.size(), GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindVertexArray(0);

	glBindVertexArray(m_particleVAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_particleVBO);
	vertexDataSize = m_particleBatch.vertices.size() * sizeof(Vertex);
	glBufferData(GL_ARRAY_BUFFER, vertexDataSize, nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertexDataSize, m_particleBatch.vertices.data());
	elementDataSize = particleIndices.size() * sizeof(GLuint);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_particleEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementDataSize, nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, elementDataSize, particleIndices.data());
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_particleBatch.textureID);
	glDrawElements(GL_TRIANGLES, particleIndices.size(), GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindVertexArray(0);


	m_lightBatch.vertices.clear();
	m_lightBatch.numSquares = 0;
	m_particleBatch.vertices.clear();
	m_particleBatch.numSquares = 0;

	m_lightShader.unbind();

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
	for (int i = 0; i < m_dynamicBatches.size(); i++) {
		if (m_dynamicBatches[i].textureID == textureID) {
			batchIndex = i;
			break;
		}
	}
	std::vector<SpriteBatch>::iterator it;
	if (batchIndex == -1) {
		m_dynamicBatches.push_back(SpriteBatch());
		it = m_dynamicBatches.end() - 1;
		it->textureID = textureID;
	}
	else {
		it = m_dynamicBatches.begin() + batchIndex;
	}

	glm::vec2 tl = position;
	glm::vec2 tr = position;
	glm::vec2 bl = position;
	glm::vec2 br = position;

	tl.x -= dimensions.x;
	tl.y += dimensions.y;
	tr += dimensions;
	bl.x -= dimensions.x;
	bl.y -= dimensions.y;
	br.x += dimensions.x;
	br.y -= dimensions.y;

	uint32_t index = it->vertices.size();
	it->vertices.resize(index + 4);
	// Add in the new vertices. Rotate each vertex
	it->vertices[index] = VertexSimple(tl, tlUV);
	it->vertices[index++].rotate(dirAngle, position);
	it->vertices[index] = VertexSimple(tr, trUV);
	it->vertices[index++].rotate(dirAngle, position);
	it->vertices[index] = VertexSimple(bl, blUV);
	it->vertices[index++].rotate(dirAngle, position);
	it->vertices[index] = VertexSimple(br, brUV);
	it->vertices[index].rotate(dirAngle, position);
	it->numSquares++;

}

void SpriteRenderer::add_static_sprite_to_batch(
	const glm::vec2& position, 
	const GLuint& textureID)
{
	int batchIndex = -1;
	// Check to see if any stored batches matches this sprites texture ID
	// If not, create a new batch
	for (int i = 0; i < m_staticBatches.size(); i++) {
		if (m_staticBatches[i].textureID == textureID) {
			batchIndex = i;
			break;
		}
	}
	std::vector<SpriteBatch>::iterator it;
	if (batchIndex == -1) {
		m_staticBatches.push_back(SpriteBatch());
		it = m_staticBatches.end() - 1;
		it->textureID = textureID;
	}
	else {
		it = m_staticBatches.begin() + batchIndex;
	}
	glm::vec2 offset = position * tileDimensions;
	glm::vec2 tl = offset;
	glm::vec2 tr = offset;
	glm::vec2 bl = offset;
	glm::vec2 br = offset;

	tl.y += tileDimensions.y;
	tr += tileDimensions;
	br.x += tileDimensions.x;

	uint32_t index = it->vertices.size();
	it->vertices.resize(index + 4);
	// Add in the new vertices. Rotate each vertex
	it->vertices[index++] = VertexSimple(tl, tlUV);
	it->vertices[index++] = VertexSimple(tr, trUV);
	it->vertices[index++] = VertexSimple(bl, blUV);
	it->vertices[index]   = VertexSimple(br, brUV);
	m_doesStaticBatchesNeedRender = true;
	it->numSquares++;


}

void SpriteRenderer::add_light_to_batch(
	const glm::vec2& position, 
	const glm::vec2& dimensions,
	const ColorRGBA32& color)
{
	glm::vec2 tl = position;
	glm::vec2 tr = position;
	glm::vec2 bl = position;
	glm::vec2 br = position;

	tl.y += dimensions.y;
	tr += dimensions;
	br.x += dimensions.x;

	uint32_t index = m_lightBatch.vertices.size();
	m_lightBatch.vertices.resize(index + 4);
	// Add in the new vertices. Rotate each vertex
	m_lightBatch.vertices[index] = Vertex(tl, tlUV);
	m_lightBatch.vertices[index++].color = color;

	m_lightBatch.vertices[index] = Vertex(tr, trUV);
	m_lightBatch.vertices[index++].color = color;

	m_lightBatch.vertices[index] = Vertex(bl, blUV);
	m_lightBatch.vertices[index++].color = color;

	m_lightBatch.vertices[index] = Vertex(br, brUV);
	m_lightBatch.vertices[index].color = color;

	m_lightBatch.numSquares++;

}

void SpriteRenderer::add_particle_to_batch(
	const glm::vec2& position, 
	const glm::vec2& dimensions, 
	const ColorRGBA32& color)
{
	glm::vec2 tl = position;
	glm::vec2 tr = position;
	glm::vec2 bl = position;
	glm::vec2 br = position;

	tl.y += dimensions.y;
	tr += dimensions;
	br.x += dimensions.x;

	uint32_t index = m_particleBatch.vertices.size();
	m_particleBatch.vertices.resize(index + 4);
	// Add in the new vertices. Rotate each vertex
	m_particleBatch.vertices[index] = Vertex(tl, tlUV);
	m_particleBatch.vertices[index++].color = color;

	m_particleBatch.vertices[index] = Vertex(tr, trUV);
	m_particleBatch.vertices[index++].color = color;

	m_particleBatch.vertices[index] = Vertex(bl, blUV);
	m_particleBatch.vertices[index++].color = color;

	m_particleBatch.vertices[index] = Vertex(br, brUV);
	m_particleBatch.vertices[index].color = color;

	m_particleBatch.numSquares++;
}

void SpriteRenderer::require_static_redraw()
{
	m_staticBatches.clear();
	m_doesStaticBatchesNeedRender = true;
}
