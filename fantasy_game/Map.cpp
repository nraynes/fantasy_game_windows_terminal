#include <string>
#include "Map.h"
#include "Object.h"

MapObject::MapObject(std::string i_name, GameObject* i_object) : name(i_name), object(i_object) {};

int Map::search(const std::string& name) {
	for (int i = 0; i < objects_list.size(); i++) {
		if (name == objects_list[i].name) {
			return i;
		}
	}
	return -1;
}

void Map::add(const std::string& name, GameObject* new_object) {
	int match = search(name);
	if (match == -1) {
		MapObject object(name, new_object);
		objects_list.push_back(object);
	}
}

void Map::remove(const std::string& name) {
	int match = search(name);
	if (match != -1) objects_list.erase(objects_list.begin() + match);
}

void Map::render() {
	for (int i = 0; i < objects_list.size(); i++) {
		MapObject* current = &objects_list[i];
		current->object->render();
	}
}