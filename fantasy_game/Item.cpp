#include "Object.cpp"

template<int H, int W>
class Item : public GameObject<H, W> {
	protected:
		short itemID;

	public:
		int value;

		Item(short new_id, Field& i_field, int x = 0, int y = 0) :
			GameObject<H, W>(i_field, x, y),
			value(10),
			itemID(new_id)
		{}

		short id() {
			return itemID;
		}
};