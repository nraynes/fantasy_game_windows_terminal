#pragma once
#include <string>
#include "Screen.h"
#include "Controller.h"
#include "Game.h"

class GameEngine {
	private:
		bool running;
		Game game;

	public:
		GameEngine();

		void start(Controller& controller, Screen& screen);

		void debug(std::string message);

		void stop();
};