#ifndef HITBOX_H
#define HITBOX_H
#include "HitboxEnum.h"
#include "Rect.h"

namespace gameEngine {
	class Hitbox : public Rect {
	protected:
		~Hitbox()
		{
		}

	public:
		Hitbox(float x, float y, float width, float height, HitboxEnum::HitboxEnums hitboxEnum);
		HitboxEnum hitboxType;
	private:		
	};
}

#endif