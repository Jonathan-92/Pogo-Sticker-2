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
		int left = myRect->x;					// left side of the rect
		int other_left = other->x;				// other rect's left side
		int right = myRect->x + myRect->w;				// etc...
		int other_right = other->x + other->w;
		int top = myRect->y;
		int other_top = other->y;
		int bottom = myRect->y + myRect->h;
		int other_bottom = other->y + other->h;

		OverlapSourceEnum* overlapSourceEnum = new OverlapSourceEnum();
		if (bottom <= other_top)  overlapSourceEnum->setOverlapSouceEnum(OverlapSourceEnum::OverlapSourceEnums::overlapsTop);
		if (top >= other_bottom)  overlapSourceEnum->setOverlapSouceEnum(OverlapSourceEnum::OverlapSourceEnums::overlapsBottom);

		if (right <= other_left)  overlapSourceEnum->setOverlapSouceEnum(OverlapSourceEnum::OverlapSourceEnums::overlapsLeft);
		if (left >= other_right)  overlapSourceEnum->setOverlapSouceEnum(OverlapSourceEnum::OverlapSourceEnums::overlapsRight);

		return *overlapSourceEnum;
	}

	bool CollisionHandling::pixelOverlaps()
	{
		return false;
	}

}