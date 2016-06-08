#ifndef COLLISIONHANDLING_H
#define COLLISIONHANDLING_H
#include "Rect.h"
#include "WorldObject.h"
#include "Character.h"

namespace gameEngine {

	/* Acts as the bounds and position which Sprites will be displayed on.
	Extends SDL_Rect and provides additional operations. */
	class CollisionHandling {
	public:
		CollisionHandling();
		~CollisionHandling();
		bool rectanglesOverlaps(Rect* myRect, Rect* other);
		bool trianglesOverlaps(Triangle* myTriangle, Triangle* other);
		bool intersect(WorldObject myWorldobject, WorldObject other);
		bool intersect(Hitbox* rectangle, WorldObject* other);
		void generateHitboxes(WorldObject worldObject);

	private:
		bool triangleRectangleOverlaps(Rect* rectangle, vector<Pointbase*> triangle);
	};
}
#endif