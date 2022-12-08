#pragma once
#include "Field.h"
#include "Object.h"

template<int H, int W>
class Item : public GameObject<H, W> {
	protected:
		short itemID;

	public:
		int value;

		Item(short new_id, Field& i_field, short i_ID, int x = 0, int y = 0);

		short id();
};