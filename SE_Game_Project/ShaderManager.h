// Created by Jeremy Bowler
// September 19, 2020

#pragma once

#include <string>
#include <unordered_map>

#include <glm/glm.hpp>
#include <GL/glew.h>

#include "ColorRGBA8.h"

class ShaderManager
{
public:
	ShaderManager();
	void init();
	void add_attributes(const std::initializer_list<std::string>& attributes);
	void add_uniform(const std::string& uniformName);
	GLint get_uniform(const std::string& uniformName);
	void compile_shader(const char* source, const GLuint shaderid);
	void link_shaders(GLuint vertexID, GLuint fragmentID);

	void bind();
	void unbind();



	void set_uniform(const std::string& name, int rhs);
	//void set_uniform(const std::string& name, float rhs);
	void set_uniform(const std::string& name, glm::vec2 rhs);
	void set_uniform(const std::string& name, glm::vec3 rhs);
	void set_uniform(const std::string& uniformName, const glm::mat4& mat);
	void set_uniform(const std::string& uniformName, const ColorRGBA8& mat);

private:
	bool m_programLinked = false;
	bool m_isActive = false;
	GLuint m_programID;
	GLuint m_attributeCount;
	// The first key is the name of the shader uniform. The second 
	// key is the GLint identifier for the shader assigned by OpenGL
	std::unordered_map<std::string, GLint> m_uniformMap;

};

