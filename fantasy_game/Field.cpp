#include <future>
#include <Windows.h>
#include <WinUser.h>
#include <mutex>
#include "Field.h"
#include "HashTable.h"

Coord::Coord() : x(0), y(0) {}
Coord::Coord(int i_x, int i_y) : x(i_x), y(i_y) {}

Point::Point(int x, int y) : solid(false), value(empty), ID(0) {}

ObjectInformation::ObjectInformation() : ID(0) {}

Field::Field() : height(fieldHeight), width(fieldWidth) {}

void Field::debug(std::string message) {
	std::wstring stemp = std::wstring(message.begin(), message.end());
	LPCWSTR sw = stemp.c_str();
	MessageBox(
		NULL,
		sw,
		(LPCWSTR)L"Controller Debug Message",
		MB_ICONINFORMATION | MB_OK | MB_DEFBUTTON1
	);
}

void Field::clear() {
	std::lock_guard<std::mutex> lock(field_mutex);
	for (int i = 0; i < fieldHeight; i++) {
		for (int j = 0; j < fieldWidth; j++) {
			matrix[i][j].value = empty;
		}
	}
}

void Field::fill(int timer, std::string message) {
	field_mutex.lock();
	for (int i = 0; i < fieldHeight; i++) {
		for (int j = 0; j < fieldWidth; j++) {
			matrix[i][j].value = j < message.size() ? message[j] : '0';
		}
	}
	field_mutex.unlock();
	std::this_thread::sleep_for(std::chrono::milliseconds(timer));
	clear();
}

void Field::track(short& ID, Coord& anchor) {
	ObjectInformation info;
	info.ID = ID;
	info.anchor.x = anchor.x;
	info.anchor.y = anchor.y;
	std::string name = std::to_string(ID);
	objects_list.add(name, info);
}

void Field::update(short& ID, Coord& anchor) {
	ObjectInformation info;
	info.ID = ID;
	info.anchor.x = anchor.x;
	info.anchor.y = anchor.y;
	std::string name = std::to_string(ID);
	objects_list.change(name, info);
}

void Field::untrack(short& ID) {
	std::string name = std::to_string(ID);
	objects_list.remove(name);
}

ObjectInformation Field::getTrackedItem(short& ID) {
	std::string name = std::to_string(ID);
	return objects_list.select(name);
}