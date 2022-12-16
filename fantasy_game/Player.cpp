#include "Player.h"
#include "Border.h"
#include "Entity.h"
#include "Field.h"

Player::Player(Field& i_field, short i_ID, int x, int y) : Entity(i_field, i_ID, x, y) {}

Border Player::getBorderCollision() {
	if (sprite->anchor.x < 0) {
		return Border::LEFT;
	} else if (sprite->anchor.y < 0) {
		return Border::TOP;
	} else if (sprite->anchor.x + sprite->width > field->width - 1) {
		return Border::RIGHT;
	} else if (sprite->anchor.y + sprite->height > field->height - 1) {
		return Border::BOTTOM;
	} else {
		return Border::NONE;
	}
}
