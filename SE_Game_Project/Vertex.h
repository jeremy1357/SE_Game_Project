// Created by Jeremy Bowler
// October 10 19, 2020

#pragma once
#include <glm/glm.hpp>
#include "ColorRGBA32.h"
#include <math.h>

struct Vertex {
	Vertex(glm::vec2 position, glm::vec2 uv) {
		this->position = position;
		this->uv = uv;
	}

	void rotate(float angle, glm::vec2 centerPoint) {
		float xx = sin(angle);
		float yy = cos(angle);

		centerPoint.x -= position.x;
		centerPoint.y -= position.y;

		glm::vec2 temp;
		temp.x = position.x * yy - position.y * xx;
		temp.y = position.x * xx + position.y * yy;

		position.x += temp.x + centerPoint.x;
		position.y += temp.y + centerPoint.y;

	}

	glm::vec2 position;
	ColorRGBA32 color;
	glm::vec2 uv;
};