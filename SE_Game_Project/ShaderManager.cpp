#include "ShaderManager.h"
#include <iostream>


const char VERT_SOURCE[] =
	"#version 410 \
	layout(location = 0) in vec2 vertex_position; \
	layout(location = 1) in vec2 vertex_uv; \
	uniform mat4 matrix; \
	out vec2 fragment_uv; \
	void main() \
	{ \
		fragment_uv = vertex_uv; \
		gl_Position.xy = (matrix * vec4(vertex_position, 0.0f, 1.0f)).xy; \
		gl_Position.z = 0.0f; \
		gl_Position.w = 1.0f; \
	}";

const char FRAG_SOURCE[] =
	"#version 410 \
	in vec2 fragment_uv; \
	out vec4 color; \
	uniform sampler2D tex; \
	void main() \
	{ \
		color = vec4(1, 0, 0, 1.0f); \
		//color = texture(tex, fragment_uv); \
	}";

ShaderManager::ShaderManager() {
	// Empty
}

void ShaderManager::init() {
	m_programID = glCreateProgram();
	if (m_programID == 0) {
		std::cout << "Failed to create a shader. Exiting program." << std::endl;
		exit(1);
	}
	// Create handles to the shaders
	GLuint vertexShaderHandle = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderHandle = glCreateShader(GL_FRAGMENT_SHADER);
	// Load vertex shader
	compile_shader(VERT_SOURCE, vertexShaderHandle);
	compile_shader(FRAG_SOURCE, fragmentShaderHandle);
	glAttachShader(m_programID, vertexShaderHandle);
	glAttachShader(m_programID, fragmentShaderHandle);
	link_shaders(vertexShaderHandle, fragmentShaderHandle);
}

void ShaderManager::link_shaders(GLuint vertexID, GLuint fragmentID) {
	glLinkProgram(m_programID);

	GLint is_linked = 0;
	glGetProgramiv(m_programID, GL_LINK_STATUS, (int*)&is_linked);


	// Debug code
	if (is_linked == GL_FALSE) {
		GLint maxLength = 0;
		glGetProgramiv(GL_FALSE, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<char> errorLog(maxLength);
		glGetProgramInfoLog(m_programID, maxLength, &maxLength, errorLog.data());
		glDeleteProgram(m_programID);
		glDeleteProgram(vertexID);
		glDeleteProgram(fragmentID);
		for (int i = 0; i < errorLog.size(); i++) {
			std::cout << errorLog[i];
		}
	}

	glDetachShader(m_programID, vertexID);
	glDetachShader(m_programID, fragmentID);
	m_programLinked = true;
	std::cout << "Shader linked successfully." << std::endl;
}

void ShaderManager::add_attributes(const std::initializer_list<std::string> & attributes)
{
	for (auto& it : attributes) {
		glBindAttribLocation(m_programID, m_attributeCount++, it.c_str());
	}
}

void ShaderManager::bind()
{
	glUseProgram(m_programID);
	m_isActive = true;

	for (int i = 0; i < m_attributeCount; i++) {
		glEnableVertexAttribArray(i);
	}
	//if (use_textures) {
	//	bind_textures();
	//}
}

void ShaderManager::unbind()
{
	m_isActive = false;
	for (int i = 0; i < m_attributeCount; i++) {
		glDisableVertexAttribArray(i);
	}
	//if (use_textures) {
	//	glBindTexture(GL_TEXTURE_2D, 0);
	//}

	glUseProgram(0);
}

void ShaderManager::add_uniform(const std::string & uniformName)
{
 	if (m_programLinked) {
 		auto it = m_uniformMap.find(uniformName);
 		if (it == m_uniformMap.end()) {
 			GLint uniformLocation = glGetUniformLocation(m_programID, uniformName.c_str());
 			m_uniformMap.emplace(uniformName, uniformLocation);
 		}
 	}
 	else {
 		std::cout << "Shader has not been linked." << std::endl;
 	}
}

GLint ShaderManager::get_uniform(const std::string & uniformName)
{
	std::unordered_map<std::string, GLint>::iterator it;
	it = m_uniformMap.find(uniformName);

	if (it != m_uniformMap.end()) {
		if (it->second != -1) {
			return it->second;
		}
		return -1;
	}
	else {
		add_uniform(uniformName);
		it = m_uniformMap.find(uniformName);
		if (it != m_uniformMap.end()) {
			return it->second;
		}
		std::cout << "Failed to load shader uniform." << std::endl;
		exit(1);
		return -1;
	}
}

void ShaderManager::set_uniform(
	const std::string & uniformName,
	glm::vec2 value) 
{
	glUniform2f(get_uniform(uniformName), value.x, value.y);
}

void ShaderManager::set_uniform(
	const std::string & uniformName, 
	glm::vec3 value) 
{
	glUniform3f(get_uniform(uniformName), value.x, value.y, value.z);
}

void ShaderManager::set_uniform(
	const std::string & uniformName, 
	int value) 
{
	glUniform1i(get_uniform(uniformName), value);
}

void ShaderManager::set_uniform(
	const std::string & uniformName, 
	const ColorRGBA8& color)
{
	glm::vec3 toVector(color.r, color.g, color.b);
	glm::vec3 copyOf = glm::normalize(toVector);
	if (m_isActive) {
		glUniform3f(get_uniform(uniformName), copyOf.x, copyOf.y, copyOf.z);
	}
	else {
		std::cout << "Shader not active\n";
	}
}

void ShaderManager::set_uniform(
	const std::string & uniformName, 
	const glm::mat4 & matrix)
{
	if (m_isActive) {
		glUniformMatrix4fv(get_uniform(uniformName), 1, GL_FALSE, &(matrix[0][0]));
	}
	else {
		std::cout << "Shader not active\n";
	}
}

//void ars::Shader::bind_textures()
//{
//	for (int i = 0; i < textureCache.size(); i++) {
//		glActiveTexture(GL_TEXTURE0 + i);
//		glBindTexture(GL_TEXTURE_2D, textureCache[i]);
//		set_uniform((textureArrayUnfrmName + "[" + std::to_string(i) + "]"), i);
//	}
//}

void ShaderManager::compile_shader(const char* source, const GLuint shaderid)
{
	glShaderSource(shaderid, 1, &source, nullptr);
	glCompileShader(shaderid);

	GLint isCompiled = 0;
	glGetShaderiv(shaderid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(shaderid, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(shaderid, maxLength, &maxLength, errorLog.data());
		glDeleteShader(shaderid);
		for (int i = 0; i < errorLog.size(); i++) {
			std::cout << errorLog[i];
		}
	}
}


