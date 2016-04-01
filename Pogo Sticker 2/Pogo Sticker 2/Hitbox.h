#ifndef HITBOX_H
#define HITBOX_H
#include "Polygon.h"
#include "HitboxEnum.h"

namespace gameEngine {
	class Hitbox : public Polygon {
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