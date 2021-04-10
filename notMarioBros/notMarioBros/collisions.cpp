#include "collisions.h"
#include "character.h"

//Initialize instance to nullptr
Collisions* Collisions::instance = nullptr;

Collisions::~Collisions() {
	delete instance;
	instance = nullptr;
}

Collisions* Collisions::Instance() {
	// If no instance exists yet of the Collisions class, then create one first, which will be the singleton object from now on.
	if (!instance) {
		instance = new Collisions;
	}

	return instance;
}

bool Collisions::Circle(Character* character1, Character* character2) {
	// Calculate the vector that seperates the two characters.
	Vector2D vec = Vector2D((character1->GetPosition().x - character2->GetPosition().x),(character1->GetPosition().y - character2->GetPosition().y));

	// Calculate the resulting vector's length
	double distance = sqrt((vec.x * vec.x) + (vec.y * vec.y));

	double combined_distance = (character1->GetCollisionRadius() + character2->GetCollisionRadius());

	// If the distance between the 2 points is shorter than both circle's radius combined, then they would be intersecting, indicating a collision.
	return distance < combined_distance;
}

bool Collisions::Circle(Vector2D point1, float radius1, Vector2D point2, float radius2) {
	// Calculate the vector that seperates the two points.
	Vector2D vec = Vector2D(point1.x - point2.x, point1.y - point2.y);

	// Calculate the resulting vector's length
	double distance = sqrt((vec.x * vec.x) + (vec.y * vec.y));

	double combined_distance = radius1 + radius2;

	// If the distance between the 2 points is shorter than both circle's radius combined, then they would be intersecting, indicating a collision.
	return distance < combined_distance;
}

bool Collisions::Box(Rect2D rect1, Rect2D rect2) {
	// If both Rectangles intersect based on the positioning of their points relative to each other, then a collision has occured.
	if (((rect1.x+rect1.width) > rect2.x) &&
		(rect1.x < (rect2.x+rect2.width)) && 
		((rect1.y + rect1.height) > rect2.y) &&
		(rect1.y < (rect2.y + rect2.height))) {
		return true;
	}

	return false;
}