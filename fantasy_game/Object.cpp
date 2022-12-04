#include <vector>
#include <future>
#include "Sprite.cpp"

template<int H, int W>
class GameObject {
	private:
		Coord anchor;

	protected:
		Field* field;
		short ID;

		void updateAnchor() {
			field->update(ID, anchor);
		}

	public:
		Sprite<H, W> sprite;
		SpriteList<H, W> spritelist;

		GameObject(Field& i_field, short i_ID, int x = 0, int y = 0) : ID(i_ID) {
			anchor.x = x;
			anchor.y = y;
			field = &i_field;
			field->track(ID, anchor);
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

		short setAnchor(int x, int y) {
			short collision = sprite.checkCollision(*field, Coord(x, y));
			if (!collision) {
				anchor.x = x;
				anchor.y = y;
			}
			updateAnchor();
			return collision;
		}

		Coord getAnchor() {
			return anchor;
		}

		short setAnchorRelativeTo(short ID, int x, int y) {
			ObjectInformation fieldItem = field->getTrackedItem(ID);	
			x += fieldItem.anchor.x;
			y += fieldItem.anchor.y;
			return setAnchor(x, y);
		}

		void render() {
			sprite.display(*field, anchor);
		}
};