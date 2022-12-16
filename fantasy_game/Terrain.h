#pragma once
#include <string>
#include <memory>
#include "SquareGrid.h"
#include "SquareGrid.cpp"
#include "Player.h"
#include "Map.h"

class Terrain {
	private:
		Map* activeArea;

	public:
		SquareGrid<Map> areas;

		Terrain(const std::string initMapName, Map* initMap);

		void removeMap(const std::string name);

		void checkRight();

		void checkLeft();

		void checkUp();

		void checkDown();

		void panRight();

		void panLeft();

		void panUp();

		void panDown();

		void setActiveMap(const std::string name);

		Map* getActiveMap();

		void render();
};