#ifndef COLLISIONHANDLING_H
#define COLLISIONHANDLING_H
#include "Rect.h"
#include "OverlapSourceEnum.h"

namespace gameEngine {

	/* Acts as the bounds and position which Sprites will be displayed on.
	Extends SDL_Rect and provides additional operations. */
	class CollisionHandling {
	public:
		CollisionHandling();
		~CollisionHandling();
		bool overlaps(Rect* myRect, Rect* other);
		OverlapSourceEnum overlapSource(Rect* myRect, Rect* other);
		bool pixelOverlaps();
	};
}
#endif