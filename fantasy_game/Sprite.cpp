#include <iostream>
#include <array>
#include <string>
#include <vector>
#include "Field.cpp"
#include "Global.h"

template<int H, int W>
struct Sprite {
	int height = H;
	int width = W;
	Point grid[H][W];
	short ID;
	Coord anchor;

	void sketch(std::string& inputStream = "-") {
		if (inputStream.size() == H * W) {
			int x = 0, y = 0;
			for (int i = 0; i < inputStream.size(); i++) {
				grid[y][x].value = inputStream[i];
				grid[y][x].ID = ID;
				x++;
				if (x >= W) {
					x = 0;
					y++;
				}
			}
		};
	}

	void setID(short& newID) {
		ID = newID;
	}

	Sprite(std::string inputStream = "-", short newID = 0) {
		if (newID != 0) {
			setID(newID);
		}
		sketch(inputStream);
	}

	short checkCollision(Field& field, Coord anchor) {
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
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

	void makeSolid() {
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				if (grid[i][j].value != empty) {
					grid[i][j].solid = true;
				}
			}
		}
	}

	void makeNotSolid() {
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				if (grid[i][j].value != empty) {
					grid[i][j].solid = false;
				}
			}
		}
	}

	void display(Field& field, Coord& i_anchor) {
		anchor.x = i_anchor.x;
		anchor.y = i_anchor.y;
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
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
};

template<int H, int W>
struct SpriteUnit {
	std::string name;
	Sprite<H, W> sprite;
};

template<int H, int W, int tableSize = 10>
class SpriteList {
	private:
		std::vector<SpriteUnit<H, W>> table[tableSize];

		int hash(std::string& name) {
			int hash = 0;
			for (int i = 0; i < name.size(); i++) {
				hash += int(name[i]);
			}
			return hash % tableSize;
		}

		bool searchBucket(std::string& name, int& index) {
			for (int i = 0; i < table[index].size(); i++) {
				if (table[index][i].name == name) {
					return true;
				}
			}
			return false;
		}

	public:
		void add(std::string& name, Sprite<H, W>& sprite) {
			SpriteUnit<H, W> unit;
			unit.name = name;
			unit.sprite = sprite;
			int index = hash(name);
			if (!searchBucket(name, index)) {
				table[index].push_back(unit);
			}
		}

		Sprite<H, W> select(std::string& name) {
			int index = hash(name);
			for (int i = 0; i < table[index].size(); i++) {
				if (table[index][i].name == name) {
					return table[index][i].sprite;
				}
			}
			return Sprite<H, W>();
		}

		void remove(std::string& name) {
			int index = hash(name);
			for (int i = 0; i < table[index].size(); i++) {
				if (table[index][i].name == name) {
					table[index].erase(table[index].begin() + i);
				}
			}
		}
};