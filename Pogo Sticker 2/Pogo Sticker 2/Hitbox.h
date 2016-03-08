#ifndef HITBOX_H
#define HITBOX_H
#include "Rect.h"
#include "HitboxEnum.h"

namespace gameEngine {
	class Hitbox : public Rect {
	public:
		Hitbox(int x, int y, int w, int h, HitboxEnum::HitboxEnums hitboxEnum);
		HitboxEnum hitboxType;
	private:		
	};
}

#endif