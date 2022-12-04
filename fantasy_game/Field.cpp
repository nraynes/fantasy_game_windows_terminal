#include <string>
#include <Windows.h>
#include <future>
#include "HashTable.cpp"
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
	Coord anchor;

	Point(int x = 0, int y = 0) : solid(false), value(empty), ID(0) {}
};

struct ObjectInformation {
	short ID;
	Coord anchor;

	ObjectInformation() : ID(0) {}
};

class Field {
	private:
		HashTable<ObjectInformation, 25> objects_list;

	public:
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

		void fill(int timer = 500, std::string message = "") {
			for (int i = 0; i < fieldHeight; i++) {
				for (int j = 0; j < fieldWidth; j++) {
					matrix[i][j].value = j < message.size() ? message[j] : '0';
				}
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(timer));
			clear();
		}

		void track(short& ID, Coord& anchor) {
			ObjectInformation info;
			info.ID = ID;
			info.anchor.x = anchor.x;
			info.anchor.y = anchor.y;
			std::string name = std::to_string(ID);
			objects_list.add(name, info);
		}

		void update(short& ID, Coord& anchor) {
			ObjectInformation info;
			info.ID = ID;
			info.anchor.x = anchor.x;
			info.anchor.y = anchor.y;
			std::string name = std::to_string(ID);
			objects_list.change(name, info);
		}

		void untrack(short& ID) {
			std::string name = std::to_string(ID);
			objects_list.remove(name);
		}

		ObjectInformation getTrackedItem(short& ID) {
			std::string name = std::to_string(ID);
			return objects_list.select(name);
		}
};