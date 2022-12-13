#include "Item.h"

Item::Item(short new_id, Field& i_field, short i_ID, int x, int y) :
	GameObject(i_field, i_ID, x, y),
	value(10),
	itemID(new_id)
{}

short Item::id() {
	return itemID;
}