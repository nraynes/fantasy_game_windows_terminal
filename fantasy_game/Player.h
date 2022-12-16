#pragma once
#include "Entity.h"
#include "Border.h"
#include "Field.h"

class Player : public Entity {
	public:
	Player(Field& i_field, short i_ID, int x, int y);

	Border getBorderCollision();
};
