#ifndef HITBOX_H
#define HITBOX_H
#include "HitboxEnum.h"
#include "Rectangle.h"

namespace gameEngine {
	class Hitbox : public Rectangle {
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