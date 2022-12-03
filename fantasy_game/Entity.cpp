#include "Object.cpp"

template<int H, int W>
class Entity : public Object<H, W> {
	public:
		int health;

		Entity(Field& i_field, int x = 0, int y = 0) : Object<H, W>(i_field, x, y), health(100) {}

		void moveRight(int amount = 1) {
			bool collision = this->sprite.checkCollision(*this->field, Coord(this->anchor.x + amount, this->anchor.y));
			if (!collision) {
				this->anchor.x += amount;
			}
		}

		void moveLeft(int amount = 1) {
			bool collision = this->sprite.checkCollision(*this->field, Coord(this->anchor.x - amount, this->anchor.y));
			if (!collision) {
				this->anchor.x -= amount;
			}
		}

		void moveUp(int amount = 1) {
			bool collision = this->sprite.checkCollision(*this->field, Coord(this->anchor.x, this->anchor.y - amount));
			if (!collision) {
				this->anchor.y -= amount;
			}
		}

		void moveDown(int amount = 1) {
			bool collision = this->sprite.checkCollision(*this->field, Coord(this->anchor.x, this->anchor.y + amount));
			if (!collision) {
				this->anchor.y += amount;
			}
		}
};