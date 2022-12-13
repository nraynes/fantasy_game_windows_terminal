#pragma once
#include <string>
#include "Field.h"

class Sprite {
	public:
		int height;
		int width;
		Point **grid;
		short ID;
		Coord anchor;

		void sketch(const std::string& inputStream);

		void setID(short& newID);

		Sprite(const int& H, const int& W, std::string inputStream = "-", short newID = 0);

		short checkCollision(Field& field, Coord anchor);

		void makeSolid();

		void makeNotSolid();

		void display(Field& field, Coord& i_anchor);
};