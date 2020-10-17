#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>

Camera::Camera() {
	// Empty
}

Camera::~Camera() {
	// Empty
}

void Camera::init_camera(
	int screenWidth,
	int screenHeight) 
{
	m_orthoMatrix = glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight);
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;
}

void Camera::update_camera(const glm::vec2& cameraPosition,
	const glm::vec2& cursorPosition,
	int screenX,
	int screenY) 
{
	// If the window size changes, refresh
	if (m_screenHeight != screenY || m_screenWidth != screenX) {
		m_orthoMatrix = glm::ortho(0.0f, (float)screenX, 0.0f, (float)screenY);
		m_screenWidth = screenX;
		m_screenHeight = screenY;
	}



	//if (m_needsUpdate) {
	//Camera Translation
	glm::vec3 translate(-cameraPosition.x + m_screenWidth / 2, -cameraPosition.y + m_screenHeight / 2, 0.0f);
	m_cameraMatrix = glm::translate(m_orthoMatrix, translate);

	//Camera Scale
	glm::vec3 scale(m_scale, m_scale, 0.0f);
	m_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * m_cameraMatrix;

	m_needsUpdate = false;
	//}


	glm::vec2 temp = cursorPosition;
	// Convert the mouse position to world position
	temp.y = screenY - temp.y;
	temp -= glm::vec2(screenX / 2.0f, screenY / 2.0f);
	temp /= m_scale;
	temp += cameraPosition;
	m_worldCursorPosition = temp;


	const glm::vec2 refAngle = glm::vec2(1.0f, 0.0f);
	glm::vec2 vectorA = glm::normalize(m_worldCursorPosition - cameraPosition);
	double dotProduct = glm::dot(vectorA, refAngle);
	double determinant = vectorA.y * refAngle.x - vectorA.x * refAngle.y;

	playerCursorAngle = atan2(determinant, dotProduct) * 180 / glm::pi<float>();

}