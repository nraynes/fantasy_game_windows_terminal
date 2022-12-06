#pragma once
#include <future>
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

		void delayMortality(bool& marker);

		void play(Field& field, Controller& controller, Screen& screen, bool& engineRunning);

		void start(Field& field, Controller& controller, Screen& screen, bool& engineRunning);

		void stop();
};