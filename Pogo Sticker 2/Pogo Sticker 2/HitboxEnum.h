#pragma once

class HitboxEnum {
public:
	typedef enum HitboxEnums {
		undefined = 0,
		characterHead = 1,
		characterBody = 2,
		characterFoot = 3,
	};

	HitboxEnums currentEnum;

	HitboxEnums getHitboxEnum() { return currentEnum; }
	void setHitboxEnum(HitboxEnums enumType) { currentEnum = enumType; }
};