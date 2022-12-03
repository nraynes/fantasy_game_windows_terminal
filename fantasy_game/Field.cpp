#include <string>
#include <Windows.h>
#include "Global.h"

struct Coord {
	int x, y;

	Coord() : x(0), y(0) {}
	Coord(int i_x, int i_y) : x(i_x), y(i_y) {}
};

struct Point {
	char value;
	bool solid;
	short ID;

	Point(int x = 0, int y = 0) : solid(false), value(empty) {}
};

struct Field {
	int height = fieldHeight;
	int width = fieldWidth;
	Point matrix[fieldHeight][fieldWidth];

	void clear() {
		for (int i = 0; i < fieldHeight; i++) {
			for (int j = 0; j < fieldWidth; j++) {
				matrix[i][j].value = empty;
			}
		}
	}

	void test(std::string message = "None") {
		for (int i = 0; i < fieldHeight; i++) {
			for (int j = 0; j < fieldWidth; j++) {
				matrix[i][j].value = j < message.size() ? message[j] : '0';
			}
		}
		Sleep(500);
		clear();
	}
};