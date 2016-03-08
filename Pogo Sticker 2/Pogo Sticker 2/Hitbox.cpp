#include "Hitbox.h"

namespace gameEngine {

	Hitbox::Hitbox(int x, int y, int w, int h, HitboxEnum::HitboxEnums hitboxEnum) :
		Rect(x, y, w, h)
	{
		hitboxType.setHitboxEnum(hitboxEnum);
	}
}
