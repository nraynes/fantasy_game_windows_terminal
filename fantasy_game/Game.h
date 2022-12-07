#pragma once
#include <future>
#include <string>
#include <vector>
#include "Field.h"
#include "Controller.h"
#include "Screen.h"

class Game {
	private:
		bool running;
		const int g_UPS;	// Global updates per second (Game Loop).
		std::future<void> gameTaskHandle;
		std::vector<std::future<void>> handles;

	public:
		Game();

		void play(Field& field, Controller& controller, Screen& screen, std::function<void()> stopEngine);

		void debug(std::string message);

		void start(Field& field, Controller& controller, Screen& screen, std::function<void()> stopEngine);

		void stop();
};