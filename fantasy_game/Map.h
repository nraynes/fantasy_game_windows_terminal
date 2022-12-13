#pragma once
#include <vector>
#include <string>
#include "Field.h"
#include "Object.h"

struct MapObject {
	std::string name;
	GameObject* object;

	MapObject(std::string i_name, GameObject* i_object);
};

class Map {
	private:
		std::vector<MapObject> objects_list;

		virtual int search(const std::string& name);

	public:

		virtual void add(const std::string& name, GameObject* new_object);

		virtual void remove(const std::string& name);

		virtual void render();
};