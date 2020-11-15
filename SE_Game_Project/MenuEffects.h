#include "Shader.h"
#include "Vertex.h"
#include "Camera.h"
#include <glm/vec2.hpp>
#include <GL/glew.h>

class MenuEffects {
public:
    MenuEffects();
    ~MenuEffects();
    void init(const std::string& projectDirectory);
    void render(const Camera& camera, glm::vec2 cursor_position);
    void update();
    float time = 0.0f;
    float x = 0.0f;
	Shader shader;
    GLuint vao;
    GLuint vbo;
    GLuint ibo;
};
