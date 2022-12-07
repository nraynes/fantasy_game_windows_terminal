#include <iostream>
#include <future>
#include <Windows.h>
#include <WinUser.h>
#include "Screen.h"

#define DEBUG 0

Screen::Screen() : output(""), FPS(120), watching(false), hold(false), debugFrame(0) {
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Screen::hideCursor() {
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hOut, &cursorInfo);
	if (cursorInfo.bVisible) {
		cursorInfo.bVisible = false;
		SetConsoleCursorInfo(hOut, &cursorInfo);
	}
}

void Screen::clearscreen() {
	COORD Position;
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}

void Screen::debug(std::string message) {
	std::wstring stemp = std::wstring(message.begin(), message.end());
	LPCWSTR sw = stemp.c_str();
	MessageBox(
		NULL,
		sw,
		(LPCWSTR)L"Screen Debug Message",
		MB_ICONINFORMATION | MB_OK | MB_DEFBUTTON1
	);
}

void Screen::render(Field& field) {
	// Clear stage...
	output = "";
	hideCursor();
	// Build stage...
	for (short i = 0; i < field.height; i++) {
		for (short j = 0; j < field.width; j++) {
			output += field.matrix[i][j].value;
		}
		output += "|\n";
	}
	int count = field.width - DEBUG;
	for (short j = 0; j <= count; j++) {
		output += "-";
	}
	if (DEBUG) {
		output += std::to_string(debugFrame);
		if (debugFrame >= 60) {
			debugFrame = 0;
		} else {
			debugFrame++;
		}
	}
	// Render stage...
	clearscreen();
	std::cout << output;
}

void Screen::pause() {
	hold = true;
}

void Screen::resume() {
	hold = false;
}

void Screen::watch(Field& field) {
	watching = true;
	while (watching) {
		if (!hold) {
			render(field);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1000 / FPS));
	}
}

void Screen::start(Field& field) {
	screenTaskHandle = std::async(std::launch::async, &Screen::watch, this, std::ref(field));
}

void Screen::stop() {
	watching = false;
	screenTaskHandle.get();
}