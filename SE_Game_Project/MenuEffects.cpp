#include "MenuEffects.h"

const std::string SPECIAL_EFFECTS_VERTEX_SHADER = "#version 330 core \n\
layout (location = 0) in vec2 vertex_position; \n\
layout (location = 1) in vec2 vertex_uv; \n\
out vec2 fragment_position; \n\
out vec2 fragment_uv; \n\
uniform mat4 camera_matrix; \n\
void main() \n\
{ \n\
    fragment_position = vertex_position; \n\
    fragment_uv = vertex_uv; \n\
    gl_Position = vec4(vertex_position, 0.0f, 1.0f); \n\
} ";

const std::string SPECIAL_EFFECTS_FRAGMENT_SHADER = "#version 330 core \n\
in vec2 fragment_position; \n\
in vec2 fragment_uv; \n\
out vec4 output_color; \n\
uniform float time; \n\
uniform vec2 resolution; \n\
uniform vec2 cursor_position; \n\
// Some useful functions \n\
vec3 mod289(vec3 x) { return x - floor(x * (1.0 / 289.0)) * 289.0; } \n\
vec2 mod289(vec2 x) { return x - floor(x * (1.0 / 289.0)) * 289.0; } \n\
vec3 permute(vec3 x) { return mod289(((x * 34.0) + 1.0) * x); } \n\
float snoise(vec2 v) { \n\
    const vec4 C = vec4(0.211324865405187, \n\
        0.366025403784439, \n\
        -0.577350269189626, \n\
        0.024390243902439); \n\
// First corner (x0) \n\
vec2 i = floor(v + dot(v, C.yy)); \n\
vec2 x0 = v - i + dot(i, C.xx); \n\
// Other two corners (x1, x2) \n\
vec2 i1 = vec2(0.0); \n\
i1 = (x0.x > x0.y) ? vec2(1.0, 0.0) : vec2(0.0, 1.0); \n\
vec2 x1 = x0.xy + C.xx - i1; \n\
vec2 x2 = x0.xy + C.zz; \n\
// Do some permutations to avoid \n\
// truncation effects in permutation \n\
i = mod289(i); \n\
vec3 p = permute( \n\
        permute(i.y + vec3(0.0, i1.y, 1.0)) \n\
            + i.x + vec3(0.0, i1.x, 1.0)); \n\
vec3 m = max(0.5 - vec3( \n\
                    dot(x0,x0), \n\
                    dot(x1,x1), \n\
                    dot(x2,x2) \n\
                    ), 0.0); \n\
m = m * m; \n\
m = m * m; \n\
vec3 x = 2.0 * fract(p * C.www) - 1.0; \n\
vec3 h = abs(x) - 0.5; \n\
vec3 ox = floor(x + 0.5); \n\
vec3 a0 = x - ox; \n\
// Normalise gradients implicitly by scaling m \n\
// Approximation of: m *= inversesqrt(a0*a0 + h*h); \n\
m *= 1.79284291400159 - 0.85373472095314 * (a0 * a0 + h * h); \n\
 \n\
// Compute final noise value at P \n\
vec3 g = vec3(0.0); \n\
g.x = a0.x * x0.x + h.x * x0.y; \n\
g.yz = a0.yz * vec2(x1.x,x2.x) + h.yz * vec2(x1.y,x2.y); \n\
return 130.0 * dot(m, g); \n\
} \n\
void main() \n\
{ \n\
    vec2 st = fragment_position.xy / resolution.xy; \n\
    // st.x *= resolution.x/resolution.y; \n\
     vec2 pos = vec2(st * 10.0); \n\
     float a = snoise(pos * vec2(cos(time * 0.1),sin(time * 0.1)) * 0.1) * 3.1415; \n\
     pos += vec2(a); \n\
     vec3 color = vec3(0.0f); \n\
     color += vec3(smoothstep(1.0, 0.0, a)); \n\
     //color += vec3(smoothstep(0.0, 1.0, a); \n\
     //olor = vec3( snoise(pos)*.5+.5 ); \n\
     gl_FragColor = vec4(color,1.0); \n\
 } \n\
";


MenuEffects::MenuEffects()
{
}

MenuEffects::~MenuEffects()
{

}

void MenuEffects::init()
{
    shader.init(SPECIAL_EFFECTS_VERTEX_SHADER.c_str(), SPECIAL_EFFECTS_FRAGMENT_SHADER.c_str());
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

    shader.set_uniform("camera_matrix", camera.m_orthoMatrix);
    shader.set_uniform("time", time);
    shader.set_uniform("resolution", glm::vec2(0.5));
    shader.set_uniform("cursor_position", cursor_position);
	glBindVertexArray(vao);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

    shader.unbind();
    x += 1.01f;
    time = sin(x);
}

void MenuEffects::update()
{
}
