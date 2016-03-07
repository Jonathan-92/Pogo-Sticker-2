#include "CollisionHandling.h"

namespace gameEngine {

	CollisionHandling::CollisionHandling()
	{
	}

	bool CollisionHandling::overlaps(Rect* myRect, Rect* other)
	{
		int left = myRect->x;					// left side of the rect
		int other_left = other->x;				// other rect's left side
		int right = myRect->x + myRect->w;				// etc...
		int other_right = other->x + other->w;
		int top = myRect->y;
		int other_top = other->y;
		int bottom = myRect->y + myRect->h;
		int other_bottom = other->y + other->h;

		if (bottom < other_top) return false;
		if (top > other_bottom) return false;

		if (right < other_left) return false;
		if (left > other_right) return false;

		return true;
	}
	
	OverlapSourceEnum CollisionHandling::overlapSource(Rect* myRect, Rect* other)
	{
		// what side of the stationaryObject does the movingObject collide on?
		bool intersectsTop = false;
		bool intersectsRight = false;

		if (myRect->x > other->x)
			intersectsRight = true;
		// y up is neg
		if (myRect->y < other->y)
			intersectsTop = true;

		OverlapSourceEnum* overlapSourceEnum = new OverlapSourceEnum();

		if (intersectsTop)
		{
			overlapSourceEnum->setOverlapSouceEnum(OverlapSourceEnum::OverlapSourceEnums::overlapsTop);
		}
		else
		{
			overlapSourceEnum->setOverlapSouceEnum(OverlapSourceEnum::OverlapSourceEnums::overlapsBottom);
		}

		if (intersectsRight)
		{
			overlapSourceEnum->setOverlapSouceEnum(OverlapSourceEnum::OverlapSourceEnums::overlapsRight);
		}
		else
		{
			overlapSourceEnum->setOverlapSouceEnum(OverlapSourceEnum::OverlapSourceEnums::overlapsLeft);
		}

		return *overlapSourceEnum;
	}

}