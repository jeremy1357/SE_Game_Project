// Created by Jeremy Bowler
// September 19, 2020

#pragma once
#include <stdint.h>

struct ColorRGBA8 
{
	ColorRGBA8(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	void operator=(const ColorRGBA8& rhs) {
		this->r = rhs.r;
		this->g = rhs.g;
		this->b = rhs.b;
		this->a = rhs.a;

	}
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
};