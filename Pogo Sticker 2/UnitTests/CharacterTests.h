#ifndef CHARACTERTESTS_H
#define CHARACTERTESTS_H
#include "character.h"

class CharacterTests : public::testing::Test{
protected:
	virtual void SetUp()
	{
		character = new Character(10, 10, 20, 50, "");
	}
	virtual void TearDown()
	{
		// Code here will be called immediately after each test
		// (right before the destructor).
	}
private:
	Character* character;
};

#endif