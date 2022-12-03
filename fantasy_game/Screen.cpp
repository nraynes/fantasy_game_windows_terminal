#include <iostream>
#include <string>
#include <future>
#include <Windows.h>
#include "Game.cpp"

class Screen {
	private:
		int FPS;
		HANDLE hOut;
		std::string output;
		std::future<void> screenTaskHandle;
		bool watching;
		short debugFrame = 0;

	public:
		Screen() : output(""), FPS(60), watching(false) {
			hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		}

		void hideCursor() {
			CONSOLE_CURSOR_INFO cursorInfo;
			GetConsoleCursorInfo(hOut, &cursorInfo);
			if (cursorInfo.bVisible) {
				cursorInfo.bVisible = false;
				SetConsoleCursorInfo(hOut, &cursorInfo);
			}
		}

		void clearscreen() {
			COORD Position;
			Position.X = 0;
			Position.Y = 0;
			SetConsoleCursorPosition(hOut, Position);
		}

		void render(Field& field) {
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
			for (short j = 0; j < field.width; j++) {
				output += "-";
			}
			output += std::to_string(debugFrame);
			if (debugFrame >= 60) {
				debugFrame = 0;
			} else {
				debugFrame++;
			}
			// Render stage...
			clearscreen();
			std::cout << output;
		}

		void watch(Field& field) {
			watching = true;
			while (watching) {
				render(field);
				std::this_thread::sleep_for(std::chrono::milliseconds(1000 / FPS));
			}
		}

		void start(Field& field) {
			screenTaskHandle = std::async(std::launch::async, &Screen::watch, this, std::ref(field));
		}

		void stop() {
			watching = false;
			screenTaskHandle.get();
		}
};