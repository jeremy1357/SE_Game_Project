#include "MenuEffects.h"

const char* SPECIAL_EFFECTS_VERTEX_SHADER = {
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

const char* SPECIAL_EFFECTS_FRAGMENT_SHADER = {
    "#version 330 core\n"
    "in vec2 fragmentUV;\n"
    "out vec4 FragColor;\n"
    "uniform sampler2D tex;\n"
    "void main()\n"
    "{ \n"
        "FragColor = texture(tex, -fragmentUV); \n"
    "} \n" };


MenuEffects::MenuEffects()
{
}

MenuEffects::~MenuEffects()
{

}

void MenuEffects::init()
{
    shader.init(SPECIAL_EFFECTS_VERTEX_SHADER, SPECIAL_EFFECTS_FRAGMENT_SHADER);
    shader.add_attributes({ "vertex_position", "vertex_uv" });
    shader.link_shaders();

    GLuint indices[6];
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 2;
    indices[4] = 3;
    indices[5] = 1;
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

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 
        2, 
        GL_FLOAT, 
        GL_FALSE, 
        sizeof(VertexSimple), 
        (void*)offsetof(VertexSimple, position));
    glVertexAttribPointer(1, 
        2, 
        GL_FLOAT, 
        GL_FALSE, 
        sizeof(VertexSimple), 
        (void*)offsetof(VertexSimple, uv));
	// Upload vertices
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);


}

void MenuEffects::render(const Camera& camera, glm::vec2 cursor_position)
{
    shader.bind();

    shader.set_uniform("camera_matrix", camera.m_orthoMatrix);
    shader.set_uniform("time", time);
    shader.set_uniform("resolution", glm::vec2(0.1));
    shader.set_uniform("cursor_position", cursor_position);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    shader.unbind();
    x += 0.01f;
    time = sin(x);
}

void MenuEffects::update()
{
}
