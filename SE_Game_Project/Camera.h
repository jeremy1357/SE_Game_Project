// Created by Jeremy Bowler
// October 10, 2020

#pragma once
#include <glm/glm.hpp>

class Camera
{
public:
	Camera();
	~Camera();
	void init_camera(int screenWidth, int screenHeight);
	// The position variable should be the players position
	void update_camera(
		const glm::vec2& cameraPosition, 
		const glm::vec2& cursorPosition,
		int screenX,
		int screenY);
	void set_scale(float scale) {
		this->m_scale = scale;
	}
	glm::vec2 get_world_cursor_position() const { return m_worldCursorPosition; }
	glm::mat4 m_orthoMatrix = glm::mat4(1.0f);
	glm::mat4 m_cameraMatrix = glm::mat4(1.0f);
	float playerCursorAngle = 0.0f;
	float m_scale = 1.0f;

private:
	glm::vec2 m_worldCursorPosition = glm::vec2(0.0f);
	int m_screenWidth				= 0;
	int	m_screenHeight				= 0;
	bool m_needsUpdate				= true;
};
