#ifndef HITBOX_H
#define HITBOX_H
#include "Polygon.h"
#include "HitboxEnum.h"

namespace gameEngine {
	class Hitbox : public Polygon {
	public:
		Hitbox(int x, int y, HitboxEnum::HitboxEnums hitboxEnum);
		HitboxEnum hitboxType;
	private:		
	};
}

#endif