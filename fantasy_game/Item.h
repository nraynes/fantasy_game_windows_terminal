#pragma once
#include "Object.h"

class Item : public GameObject {
	protected:
		short itemID;

	public:
		int value;

		Item(short new_id, Field& i_field, short i_ID, int x = 0, int y = 0);

		short id();
};