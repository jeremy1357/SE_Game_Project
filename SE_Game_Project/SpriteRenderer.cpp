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

	glGenVertexArrays(1, &m_staticVAO);
	glGenBuffers(1, &m_staticVBO);
	glGenBuffers(1, &m_staticEBO);

	glBindVertexArray(m_staticVAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_staticVBO);


	// Each vertex object contains three attributes.
	// 1) Position -> glm::vec2
	// 2) UV -> glm::vec2
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
		sizeof(VertexSimple), (void*)offsetof(VertexSimple, position));

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
		sizeof(VertexSimple), (void*)offsetof(VertexSimple, uv));


	// Element buffer to store vertex indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_staticEBO);
	glBindVertexArray(0);







	//glGenVertexArrays(1, &m_dynamicVAO);
	//glGenBuffers(1, &m_dynamicVBO);
	//glBindVertexArray(m_dynamicVAO);
	//glBindBuffer(GL_ARRAY_BUFFER, m_dynamicVBO);


	//// Each vertex object contains three attributes.
	//// 1) Position -> glm::vec2
	//// 2) UV -> glm::vec2
	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
	//	sizeof(VertexSimple), (void*)offsetof(VertexSimple, position));
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
	//	sizeof(VertexSimple), (void*)offsetof(VertexSimple, uv));
	//glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);

	//// Element buffer to store vertex indices
	//glGenBuffers(1, &m_dynamicEBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_dynamicEBO);
	//glBindVertexArray(0);

}

void SpriteRenderer::on_update()
{

}

void SpriteRenderer::on_render()
{
	//for (auto& batch : m_dynamicBatches) {
	//	batch.indices.resize(batch.vertices.size() * 6);
	//	GLuint startIndex = 0;
	//	for (size_t x = 0; x < batch.indices.size(); x += 6) {
	//		// Store vertex indices 
	//		batch.indices[x] = startIndex;
	//		batch.indices[x + 1] = (startIndex + 1);
	//		batch.indices[x + 2] = (startIndex + 2);
	//		batch.indices[x + 3] = (startIndex + 2);
	//		batch.indices[x + 4] = (startIndex + 1);
	//		batch.indices[x + 5] = (startIndex + 3);
	//		startIndex += 4;
	//	}
	//}





	if (m_doesStaticBatchesNeedRender) {
		m_doesStaticBatchesNeedRender = false;
		std::vector<GLuint> indexOffsets;
		//for (auto& batch : m_staticBatches) {
		//	batch.indices.resize(batch.vertices.size() * 6);
		//	GLuint startIndex = 0;
		//	for (size_t x = 0; x < batch.indices.size(); x += 6) {
		//		// Store vertex indices 
		//		batch.indices[x] = startIndex;
		//		batch.indices[x + 1] = (startIndex + 1);
		//		batch.indices[x + 2] = (startIndex + 2);
		//		batch.indices[x + 3] = (startIndex + 2);
		//		batch.indices[x + 4] = (startIndex + 1);
		//		batch.indices[x + 5] = (startIndex + 3);
		//		startIndex += 4;
		//	}
		//}
		int xx = 0;
		GLuint startIndex = 0;

		for (auto& batch : m_staticBatches) {
			for (int c = 0; c < batch.vertices.size(); c++) {
				staticVertices.push_back(batch.vertices[c]);
			}
			GLuint offsetIndex = 0;
			if (xx != 0) {
				for (int j = 0; j < m_staticBatches.size() - 1; j++) {
					offsetIndex += m_staticBatches[j].numSquares * 6;
				}
			}
			xx += 1;
			indexOffsets.push_back(offsetIndex);
			//staticVertices.insert(std::end(staticVertices), std::begin(batch.vertices), std::end(batch.vertices));
			for (size_t x = 0; x < batch.numSquares; x++) {
				// Store vertex indices 
				allIndices.push_back(startIndex);
				allIndices.push_back(startIndex + 1);
				allIndices.push_back(startIndex + 2);
				allIndices.push_back(startIndex + 2);
				allIndices.push_back(startIndex + 1);
				allIndices.push_back(startIndex + 3);
				startIndex += 4;
			}
		}

		glBindVertexArray(m_staticVAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_staticVBO);
		GLuint vertexDataSize = staticVertices.size() * sizeof(VertexSimple);
		glBufferData(GL_ARRAY_BUFFER, vertexDataSize, &staticVertices[0], GL_DYNAMIC_DRAW);
		//glBufferSubData(GL_ARRAY_BUFFER, 0, vertexDataSize, );

		GLuint elementDataSize = allIndices.size() * sizeof(GLuint);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_staticEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementDataSize, &allIndices[0], GL_DYNAMIC_DRAW);
		//glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, elementDataSize, );
		

		glBindVertexArray(0);




		// Bind shader
		m_shader.bind();
		m_shader.set_uniform("tex", 0);

		glm::mat4 projectionMatrix = m_camera->m_cameraMatrix;
		m_shader.set_uniform("cameraMatrix", projectionMatrix);


		glBindVertexArray(m_staticVAO);
		glActiveTexture(GL_TEXTURE0);

		int k = 0;
		auto& batch = m_staticBatches[0];
		for (auto& batch : m_staticBatches) {
			GLuint s = indexOffsets[k];
			GLuint e = indexOffsets[k] + batch.numSquares * 6 - 1;
			GLuint num = batch.numSquares * 6;

			glBindTexture(GL_TEXTURE_2D, batch.textureID);
			//glDrawRangeElements(GL_TRIANGLES, s, e, num, GL_UNSIGNED_INT, &allIndices);
			glDrawElements(GL_TRIANGLES, batch.numSquares * 6, GL_UNSIGNED_INT, (void*)(indexOffsets[k]));
			k += 1;

		}
		glBindTexture(GL_TEXTURE_2D, 0);

		glBindVertexArray(0);
		m_shader.unbind();
		m_staticBatches.clear();
		allIndices.clear();
		staticVertices.clear();
	}





	//glBindVertexArray(m_dynamicVAO);

	//for (auto& batch : m_dynamicBatches) {
	//	glActiveTexture(GL_TEXTURE0);
	//	glBindTexture(GL_TEXTURE_2D, batch.textureID);

	//	glBindBuffer(GL_ARRAY_BUFFER, m_dynamicVBO);
	//	GLuint vertexDataSize = batch.vertices.size() * sizeof(VertexSimple);
	//	glBufferData(GL_ARRAY_BUFFER, vertexDataSize, nullptr, GL_DYNAMIC_DRAW);
	//	glBufferSubData(GL_ARRAY_BUFFER, 0, vertexDataSize, batch.vertices.data());

	//	GLuint elementDataSize = batch.indices.size() * sizeof(GLuint);
	//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_dynamicEBO);
	//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementDataSize, nullptr, GL_DYNAMIC_DRAW);
	//	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, elementDataSize, batch.indices.data());

	//	glDrawElements(GL_TRIANGLES, batch.indices.size(), GL_UNSIGNED_INT, 0);
	//}
	//glBindTexture(GL_TEXTURE_2D, 0);
	//glBindVertexArray(0);

	//m_shader.unbind();

	// At the end of each render. Clear batches
	m_dynamicBatches.clear();

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
	tr.x += dimensions.x;
	tr.y += dimensions.y;
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
