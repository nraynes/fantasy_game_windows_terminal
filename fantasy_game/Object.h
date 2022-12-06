#pragma once
#include "Sprite.h"
#include "Sprite.cpp"
#include "Field.h"
#include "HashTable.h"

template<int H, int W>
class GameObject {
	private:
		Coord anchor;

	protected:
		Field* field;
		short ID;

		void updateAnchor();

	public:
		Sprite<H, W> sprite;
		HashTable<Sprite<H, W>> spritelist;

		GameObject(Field& i_field, short i_ID, int x = 0, int y = 0);

		void addSprite(std::string name, std::string inputStream = empty);

		void setSprite(std::string name);

		void removeSprite(std::string name);

		void makeSolid();

		void makeNotSolid();

		short setAnchor(int x, int y);

		Coord getAnchor();

		short setAnchorRelativeTo(short ID, int x, int y);

		void render();
};