#include <string>
#include "Terrain.h"
#include "Map.h"
#include "SquareGrid.h"

Terrain::Terrain(const std::string initMapName, Map* initMap) : areas(initMapName, *initMap), activeArea(initMap) {};
