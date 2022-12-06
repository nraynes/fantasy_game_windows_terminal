#pragma once
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
};