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
	void update_camera(glm::vec2 position);
	void set_scale(float scale) {
		this->m_scale = scale;
	}
	glm::mat4 m_orthoMatrix = glm::mat4(1.0f);
	glm::mat4 m_cameraMatrix = glm::mat4(1.0f);
private:
	int m_screenWidth = 0;
	int	m_screenHeight = 0;
	float m_scale = 1.0f;
	bool m_needsUpdate = true;
};
