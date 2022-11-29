static const int fieldHeight = 29;
static const int fieldWidth = 110;
static const char empty = '-';

struct Coord {
	int x, y;
};

struct Point {
	char value;
	Coord location;
	bool solid;

	Point(int x = 0, int y = 0) : solid(false), value(empty) {
		location.x = x;
		location.y = y;
	}
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
};