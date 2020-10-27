// Created by Jeremy Bowler
// October 10 19, 2020

#pragma once
#define _USE_MATH_DEFINES

#include <glm/glm.hpp>
#include "ColorRGBA32.h"
#include <math.h>

struct Vertex {
	Vertex() {
		position = glm::vec2(0.0f);
		uv = glm::vec2(0.0f);
	}

	Vertex(const glm::vec2& position, const glm::vec2& uv) {
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
	glm::vec2 uv;
	ColorRGBA32 color;

};

struct VertexSimple {
	VertexSimple() {
		this->position = glm::vec2(0.0);
		this->uv = glm::vec2(0.0);
	}
	VertexSimple(const glm::vec2& position, const glm::vec2& uv) {
		this->position = position;
		this->uv = uv;
	}

	void rotate(float angle, glm::vec2 centerPoint) {
		float s = sin(angle * M_PI / 180.0);
		float c = cos(angle * M_PI / 180.0);

		position -= centerPoint;

		glm::vec2 temp;
		temp.x = position.x * c - position.y * s;
		temp.y = position.x * s + position.y * c;

		position.x = temp.x + centerPoint.x;
		position.y = temp.y + centerPoint.y;

	}

	glm::vec2 position;
	glm::vec2 uv;
};