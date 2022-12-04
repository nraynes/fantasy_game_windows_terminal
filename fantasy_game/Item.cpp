#include "Object.cpp"

template<int H, int W>
class Item : public GameObject<H, W> {
	protected:
		short itemID; // itemID is used by the game to track items, where as the ID is used by the game engine to track objects and sprites displayed on the field.

	public:
		int value;

		Item(short new_id, Field& i_field, short i_ID, int x = 0, int y = 0) :
			GameObject<H, W>(i_field, i_ID, x, y),
			value(10),
			itemID(new_id)
		{}

		short id() {
			return itemID;
		}
};