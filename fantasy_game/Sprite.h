#pragma once
#include "Field.h"

template<int H, int W>
struct Sprite {
	int height;
	int width;
	Point grid[H][W];
	short ID;
	Coord anchor;

	void sketch(std::string& inputStream = "-");

	void setID(short& newID);

	Sprite(std::string inputStream = "-", short newID = 0);

	short checkCollision(Field& field, Coord anchor);

	void makeSolid();

	void makeNotSolid();

	void display(Field& field, Coord& i_anchor);
};