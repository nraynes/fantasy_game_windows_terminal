#pragma once
#include <string>
#include "Sprite.h"
#include "Field.h"
#include "HashTable.h"

class GameObject {
	private:
		Coord anchor;

	protected:
		Field* field;
		short ID;
		bool solid;

		virtual void updateAnchor();

	public:
		Sprite* sprite;
		HashTable<Sprite*> spritelist;

		GameObject(Field& i_field, short i_ID, int x = 0, int y = 0);

		virtual void addSprite(int H, int W, std::string name, std::string inputStream = std::to_string(empty));

		virtual void setSprite(std::string name);

		virtual void removeSprite(std::string name);

		virtual void makeSolid();

		virtual void makeNotSolid();

		virtual short setAnchor(int x, int y);

		virtual Coord getAnchor();

		virtual short setAnchorRelativeTo(short ID, int x, int y);

		virtual void render();
};