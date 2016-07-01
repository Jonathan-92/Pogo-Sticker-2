#include "Hitbox.h"
#include "GameEngine.h"

namespace gameEngine {

	Hitbox::Hitbox(float x, float y, float width, float height, HitboxEnum::HitboxEnums hitboxEnum) :
		Rectangle(x, y, width, height)
	{
		hitboxType.setHitboxEnum(hitboxEnum);
	}
}
