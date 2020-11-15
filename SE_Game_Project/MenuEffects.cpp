#include "MenuEffects.h"
#include <fstream>

MenuEffects::MenuEffects()
{
}

MenuEffects::~MenuEffects()
{

}

void MenuEffects::init(const std::string& projectDirectory)
{
    const std::string fragShader = projectDirectory + "\\Resources\\Shaders\\menu_effect.frag";
    const std::string vertShader = projectDirectory + "\\Resources\\Shaders\\menu_effect.vert";
    std::string fragmentBuffer;
    std::string vertexBuffer;
    
    std::ifstream file(fragShader, std::ios::binary);
    if (file.fail()) {
        perror(fragShader.c_str());
        return;
    }
    file.seekg(0, std::ios::end);
    int fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    fileSize -= file.tellg();
    fragmentBuffer.resize(fileSize);
    file.read((char*)&(fragmentBuffer[0]), fileSize);
    file.close();
    std::ifstream file2(vertShader, std::ios::binary);
    if (file2.fail()) {
        perror(vertShader.c_str());
        return;
    }
    file2.seekg(0, std::ios::end);
    fileSize = file2.tellg();
    file2.seekg(0, std::ios::beg);
    fileSize -= file2.tellg();
    vertexBuffer.resize(fileSize);
    file2.read((char*)&(vertexBuffer[0]), fileSize);
    file2.close();


    shader.init(vertexBuffer.c_str(), fragmentBuffer.c_str());
    shader.add_attributes({ "vertex_position", "vertex_uv" });
    shader.link_shaders();

    GLuint indices[6];
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 2;
    indices[4] = 3;
    indices[5] = 1;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
		sizeof(VertexSimple), (void*)offsetof(VertexSimple, position));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
		sizeof(VertexSimple), (void*)offsetof(VertexSimple, uv));



	// Upload indices
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW);

    VertexSimple vertices[4];
    vertices[0].position = glm::vec2(-1.0f, -1.0f);
    vertices[0].uv = glm::vec2(0.0f);
    vertices[1].position = glm::vec2(-1.0f, 1.0f);
    vertices[1].uv = glm::vec2(0.0f, 1.0f);
    vertices[2].position = glm::vec2(1.0f, -1.0f);
    vertices[2].uv = glm::vec2(1.0f, 0.0f);
    vertices[3].position = glm::vec2(1.0f, 1.0f);
    vertices[3].uv = glm::vec2(1.0f, 1.0f);


	// Upload vertices
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);
	glBindVertexArray(0);
}

void MenuEffects::render(const Camera& camera, glm::vec2 cursor_position)
{
    shader.bind();

    //shader.set_uniform("camera_matrix", camera.m_orthoMatrix);
    shader.set_uniform("time", x);
    shader.set_uniform("resolution", glm::vec2(0.9));
    //shader.set_uniform("mouse", cursor_position);
	glBindVertexArray(vao);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

    shader.unbind();
    x += 0.01;
    time = sin(x);
}

void MenuEffects::update()
{
}
