#pragma once

class OverlapSourceEnum {
public:
	typedef enum OverlapSourceEnums {
		overlapsTop = 1,
		overlapsRight = 2,
		overlapsBottom = 3,
		overlapsLeft = 4,
	};

	OverlapSourceEnums currentEnum;

	OverlapSourceEnums getOverlapSouceEnum() { return currentEnum; }
	void setOverlapSouceEnum(OverlapSourceEnums enumType){ currentEnum = enumType; }
};