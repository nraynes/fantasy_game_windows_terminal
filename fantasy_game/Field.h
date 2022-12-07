#pragma once
#include <string>
#include "HashTable.h"
#include "HashTable.cpp"

const int fieldHeight = 29;
const int fieldWidth = 110;
const char empty = ' ';

struct Coord {
	int x, y;

	Coord();
	Coord(int i_x, int i_y);
};

struct ObjectInformation {
	short ID;
	Coord anchor;

	ObjectInformation();
};

struct Point {
	char value;
	bool solid;
	short ID;
	Coord anchor;

	Point(int x = 0, int y = 0);
};

class Field {
	private:
		HashTable<ObjectInformation, 25> objects_list;

	public:
		const int height;
		const int width;
		Point matrix[fieldHeight][fieldWidth];

		Field();

		void debug(std::string message);

		void clear();

		void fill(int timer = 500, std::string message = "");

		void track(short& ID, Coord& anchor);

		void update(short& ID, Coord& anchor);

		void untrack(short& ID);

		ObjectInformation getTrackedItem(short& ID);
};