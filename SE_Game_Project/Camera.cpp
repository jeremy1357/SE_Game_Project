#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() {
	// Empty
}

Camera::~Camera() {
	// Empty
}

void Camera::init_camera(const int screenWidth, const int screenHeight) {
	m_orthoMatrix = glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight);
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;
}

void Camera::update_camera(glm::vec2 position) {
	//if (m_needsUpdate) {
	//Camera Translation
	glm::vec3 translate(-position.x + m_screenWidth / 2, -position.y + m_screenHeight / 2, 0.0f);
	m_cameraMatrix = glm::translate(m_orthoMatrix, translate);

	//Camera Scale
	glm::vec3 scale(m_scale, m_scale, 0.0f);
	m_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * m_cameraMatrix;

	m_needsUpdate = false;
	//}
}