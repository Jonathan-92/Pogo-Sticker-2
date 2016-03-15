#include "Hitbox.h"
#include "GameEngine.h"

namespace gameEngine {

	Hitbox::Hitbox(int x, int y, HitboxEnum::HitboxEnums hitboxEnum) :
		Polygon(x, y)
	{
		hitboxType.setHitboxEnum(hitboxEnum);
	}
}
