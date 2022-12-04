#include <vector>
#include <future>
#include "Sprite.cpp"

template<int H, int W>
class GameObject {
	protected:
		Coord anchor;
		Field* field;
		short ID;

	public:
		Sprite<H, W> sprite;
		SpriteList<H, W> spritelist;

		GameObject(Field& i_field, int x = 0, int y = 0) : ID(0) {
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
			bool collision = sprite.checkCollision(*field, *(new Coord(x, y)));
			if (!collision) {
				anchor.x = x;
				anchor.y = y;
			}
		}

		void setAnchorRelativeTo(short ID, int x, int y) {
			Coord relativeAnchor;
			relativeAnchor.x = 0;
			relativeAnchor.y = 0;
			bool breakLoop = false;
			for(int i = 0; i < field->height; i++) {
				for (int j = 0; j < field->width; j++) {
					if (field->matrix[i][j].ID == ID) {
						relativeAnchor.x = field->matrix[i][j].anchor.x;
						relativeAnchor.y = field->matrix[i][j].anchor.y;
						breakLoop = true;
						break;
					}
				}
				if (breakLoop == true) break;
			}
			x += relativeAnchor.x;
			y += relativeAnchor.y;
			setAnchor(x, y);
		}

		void render() {
			sprite.display(*field, anchor);
		}
};