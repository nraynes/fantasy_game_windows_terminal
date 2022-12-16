#include <vector>
#include <memory>
#include "Object.h"

void GameObject::updateAnchor() {
	field->update(ID, anchor);
}

GameObject::GameObject(Field& i_field, short i_ID, int x, int y) : ID(i_ID), sprite(nullptr), solid(false) {
	anchor.x = x;
	anchor.y = y;
	field = &i_field;
	field->track(ID, anchor);
}

void GameObject::addSprite(int H, int W, std::string name, std::string inputStream) {
	Sprite* newSprite = new Sprite(H, W, inputStream, ID);
	if (solid) newSprite->makeSolid();
	spritelist.add(name, newSprite);
}

void GameObject::setSprite(std::string name) {
	sprite = spritelist.select(name);
}

void GameObject::removeSprite(std::string name) {
	spritelist.remove(name);
}

void GameObject::makeSolid() {
	solid = true;
	sprite->makeSolid();
	spritelist.forEachItem([](Sprite* item) {
		item->makeSolid();
	});
}

void GameObject::makeNotSolid() {
	solid = false;
	sprite->makeNotSolid();
	spritelist.forEachItem([](Sprite* item) {
		item->makeNotSolid();
	});
}

short GameObject::setAnchor(int x, int y) {
	short collision = sprite->checkCollision(*field, Coord(x, y));
	if (!collision) {
		anchor.x = x;
		anchor.y = y;
		updateAnchor();
	}
	return collision;
}

Coord GameObject::getAnchor() {
	return anchor;
}

short GameObject::setAnchorRelativeTo(short ID, int x, int y) {
	ObjectInformation fieldItem = field->getTrackedItem(ID);	
	x += fieldItem.anchor.x;
	y += fieldItem.anchor.y;
	return setAnchor(x, y);
}

void GameObject::render() {
	sprite->display(*field, anchor);
}