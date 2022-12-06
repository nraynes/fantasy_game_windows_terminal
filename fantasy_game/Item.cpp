#include "Item.h"

template<int H, int W>
Item<H, W>::Item(short new_id, Field& i_field, short i_ID, int x, int y) :
	GameObject<H, W>(i_field, i_ID, x, y),
	value(10),
	itemID(new_id)
{}

template<int H, int W>
short Item<H, W>::id() {
	return itemID;
}