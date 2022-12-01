#include <vector>
#include "Sprite.cpp"

template<int H, int W>
class Entity {
	private:
		Coord anchor;
		Field* field;


	public:
		Sprite<H, W> sprite;
		SpriteList<H, W> spritelist;

		Entity(Field& i_field, int x = 0, int y = 0) {
			anchor.x = x;
			anchor.y = y;
			field = &i_field;
		}

		void addSprite(std::string name, std::string inputStream = empty) {
			Sprite<H, W> newSprite = Sprite<H, W>(inputStream);
			spritelist.add(name, newSprite);
		}

		void setSprite(std::string name) {
			sprite = spritelist.select(name);
		}

		void removeSprite(std::string name) {
			spritelist.remove(name);
		}

		void setAnchor(int x, int y) {
			bool collision = sprite.checkCollision(*field, new Coord(x, y));
			if (!collision) {
				anchor.x = x;
				anchor.y = y;
			}
		}

		void moveRight(int amount = 1) {
			bool collision = sprite.checkCollision(*field, Coord(anchor.x + amount, anchor.y));
			if (!collision) {
				anchor.x += amount;
			}
		}

		void moveLeft(int amount = 1) {
			bool collision = sprite.checkCollision(*field, Coord(anchor.x - amount, anchor.y));
			if (!collision) {
				anchor.x -= amount;
			}
		}

		void moveUp(int amount = 1) {
			bool collision = sprite.checkCollision(*field, Coord(anchor.x, anchor.y - amount));
			if (!collision) {
				anchor.y -= amount;
			}
		}

		void moveDown(int amount = 1) {
			bool collision = sprite.checkCollision(*field, Coord(anchor.x, anchor.y + amount));
			if (!collision) {
				anchor.y += amount;
			}
		}

		void render() {
			 sprite.display(*field, anchor);
		}
};