#include <iostream>
#include <array>
#include <string>
#include <vector>
#include "Sprite.h"
#include "Field.h"

void Sprite::sketch(const std::string& inputStream) {
	int fullSize = height * width;
	if (inputStream.size() == fullSize) {
		int x = 0, y = 0;
		for (int i = 0; i < inputStream.size(); i++) {
			grid[y][x].value = inputStream[i];
			grid[y][x].ID = ID;
			x++;
			if (x >= width) {
				x = 0;
				y++;
			}
		}
	}
}

void Sprite::setID(short& newID) {
	ID = newID;
}

Sprite::Sprite(const int& H, const int& W, std::string inputStream, short newID) : height(H), width(W) {
	/*Point* sub = new Point[W];
	grid = (Point**)calloc(H, sizeof(*sub));*/

	grid = new Point*[H];
	for (int i = 0; i < H; i++) {
		grid[i] = new Point[W];
	}
	if (newID != 0) {
		setID(newID);
	}
	sketch(inputStream);
}

short Sprite::checkCollision(Field& field, Coord anchor) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			int curY = anchor.y + i;
			int curX = anchor.x + j;
			if (grid[i][j].value != empty) {
				if (
					curY > field.height - 1
					|| curY < 0
					|| curX > field.width - 1
					|| curX < 0
					) {
					return -1;	// -1 means colliding with the border.
				}
				if (field.matrix[curY][curX].ID != ID && field.matrix[curY][curX].solid) {
					return field.matrix[curY][curX].ID;	// Any other number is the ID of the object this sprite is colliding with.
				}
			}
		}
	}
	return 0;	// 0 means not colliding.
}

void Sprite::makeSolid() {
	solid = true;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (grid[i][j].value != empty) {
				grid[i][j].solid = true;
			}
		}
	}
}

void Sprite::makeNotSolid() {
	solid = false;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (grid[i][j].solid) {
				grid[i][j].solid = false;
			}
		}
	}
}

void Sprite::display(Field& field, Coord& i_anchor) {
	anchor.x = i_anchor.x;
	anchor.y = i_anchor.y;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			int curY = i_anchor.y + i;
			int curX = i_anchor.x + j;
			if (grid[i][j].value != empty) {
				field.matrix[curY][curX].value = grid[i][j].value;
				field.matrix[curY][curX].solid = grid[i][j].solid;
				field.matrix[curY][curX].ID = grid[i][j].ID;
				field.matrix[curY][curX].anchor.x = i_anchor.x;
				field.matrix[curY][curX].anchor.y = i_anchor.y;
			}
		}
	}
}