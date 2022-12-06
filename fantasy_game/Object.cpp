#include <vector>
#include <future>
#include "Object.h"

template<int H, int W>
void GameObject<H, W>::updateAnchor() {
	field->update(ID, anchor);
}

template<int H, int W>
GameObject<H, W>::GameObject(Field& i_field, short i_ID, int x, int y) : ID(i_ID) {
	anchor.x = x;
	anchor.y = y;
	field = &i_field;
	field->track(ID, anchor);
}

template<int H, int W>
void GameObject<H, W>::addSprite(std::string name, std::string inputStream) {
	Sprite<H, W> newSprite = Sprite<H, W>(inputStream, ID);
	spritelist.add(name, newSprite);
}

template<int H, int W>
void GameObject<H, W>::setSprite(std::string name) {
	sprite = spritelist.select(name);
}

template<int H, int W>
void GameObject<H, W>::removeSprite(std::string name) {
	spritelist.remove(name);
}

template<int H, int W>
void GameObject<H, W>::makeSolid() {
	sprite.makeSolid();
}

template<int H, int W>
void GameObject<H, W>::makeNotSolid() {
	sprite.makeNotSolid();
}

template<int H, int W>
short GameObject<H, W>::setAnchor(int x, int y) {
	short collision = sprite.checkCollision(*field, Coord(x, y));
	if (!collision) {
		anchor.x = x;
		anchor.y = y;
	}
	updateAnchor();
	return collision;
}

template<int H, int W>
Coord GameObject<H, W>::getAnchor() {
	return anchor;
}

template<int H, int W>
short GameObject<H, W>::setAnchorRelativeTo(short ID, int x, int y) {
	ObjectInformation fieldItem = field->getTrackedItem(ID);	
	x += fieldItem.anchor.x;
	y += fieldItem.anchor.y;
	return setAnchor(x, y);
}

template<int H, int W>
void GameObject<H, W>::render() {
	sprite.display(*field, anchor);
}