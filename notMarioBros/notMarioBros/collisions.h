#pragma once
#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "commons.h"

class Character;

// Singleton class used for querying Bounding box and circle collisions.
class Collisions
{
public:
	~Collisions();

	// Return a pointer to the singleton Collisions class object so that requests for a collision check can be made.
	static Collisions* Instance();

	// Bounding circle
	bool Circle(Character* character1, Character* character2);
	bool Circle(Vector2D point1, float radius1, Vector2D point2, float radius2);

	// Bounding box
	bool Box(Rect2D rect1, Rect2D rect2);

private:

	static Collisions* instance;
};

#endif