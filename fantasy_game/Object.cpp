#include <vector>
#include <future>
#include "Sprite.cpp"

template<int H, int W>
class Object {
	protected:
		Coord anchor;
		Field* field;
		short ID;

	public:
		Sprite<H, W> sprite;
		SpriteList<H, W> spritelist;

		Object(Field& i_field, int x = 0, int y = 0) : ID(0) {
			anchor.x = x;
			anchor.y = y;
			field = &i_field;
		}

		void setID(short& newID) {
			ID = newID;
		}

		void addSprite(std::string name, std::string inputStream = empty) {
			Sprite<H, W> newSprite = Sprite<H, W>(inputStream, ID);
			spritelist.add(name, newSprite);
		}

		void setSprite(std::string name) {
			sprite = spritelist.select(name);
		}

		void removeSprite(std::string name) {
			spritelist.remove(name);
		}

		void makeSolid() {
			sprite.makeSolid();
		}

		void makeNotSolid() {
			sprite.makeNotSolid();
		}

		void setAnchor(int x, int y) {
			bool collision = sprite.checkCollision(*field, new Coord(x, y));
			if (!collision) {
				anchor.x = x;
				anchor.y = y;
			}
		}

		void render() {
			sprite.display(*field, anchor);
		}
};