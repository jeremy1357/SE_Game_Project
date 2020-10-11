// Created by Jeremy Bowler
// October 10 19, 2020

#pragma once
#include <glm/glm.hpp>
#include "ColorRGBA32.h"

struct Vertex {
	Vertex(glm::vec2 position, glm::vec2 uv) {
		this->position = position;
		this->uv = uv;
	}
	glm::vec2 position;
	ColorRGBA32 color;
	glm::vec2 uv;
};