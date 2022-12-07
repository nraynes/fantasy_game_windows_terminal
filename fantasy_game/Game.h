#pragma once
#include <future>
#include <atomic>
#include <string>
#include "Field.h"
#include "Controller.h"
#include "Screen.h"

class Game {
	private:
		bool running;
		int g_UPS;	// Global updates per second (Game Loop).
		std::future<void> gameTaskHandle;
		std::future<void> delayHandle;

	public:
		Game();

		void delayMortality(std::atomic<bool>& marker);

		void play(Field& field, Controller& controller, Screen& screen, std::function<void()> stopEngine);

		void debug(std::string message);

		void start(Field& field, Controller& controller, Screen& screen, std::function<void()> stopEngine);

		void stop();
};