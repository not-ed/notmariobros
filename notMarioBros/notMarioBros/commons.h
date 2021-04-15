#pragma once
#ifndef COMMONS_H
#define COMMONS_H

struct Vector2D
{
	float x;
	float y;

	Vector2D() {
		x = 0.0f;
		y = 0.0f;
	}

	Vector2D(float initial_x, float initial_y) {
		x = initial_x;
		y = initial_y;
	}
};

struct IntVector2D {
	int x;
	int y;

	IntVector2D() {
		x = 0.0f;
		y = 0.0f;
	}

	IntVector2D(int initial_x, int initial_y) {
		x = initial_x;
		y = initial_y;
	}
};

enum SCREENS {
	SCREEN_MENU,
	SCREEN_LEVEL1,
	SCREEN_LEVEL1_2P
};

enum FACING {
	FACING_LEFT,
	FACING_RIGHT
};

struct Rect2D {
	float x;
	float y;
	float width;
	float height;

	Rect2D(float x_pos, float y_pos, float width, float height) {
		x = x_pos;
		y = y_pos;
		this->width = width;
		this->height = height;
	}
};

#endif