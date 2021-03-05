#pragma once
#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "commons.h"

class Character;

class Collisions
{
public:
	~Collisions();

	static Collisions* Instance();

	bool Circle(Character* character1, Character* character2);
	bool Circle(Vector2D point1, float radius1, Vector2D point2, float radius2);
	bool Box(Rect2D rect1, Rect2D rect2);

private:
	Collisions();

	static Collisions* m_instance;
};

#endif