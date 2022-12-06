#include <iostream>
#include "Engine.h"


GameEngine::GameEngine() : running(false) {};

void GameEngine::start(Controller& controller, Screen& screen) {
	running = true;
	Field playingField;
	game.start(playingField, controller, screen, running);
	screen.start(playingField);
	controller.listen();
	while (running) {
		if (controller.checkInput(Input::ESCAPE)) {
			running = false;
		}
	}
	controller.stopListening();
	screen.stop();
	game.stop();
	std::cout << "\nGame Engine stopped...\n";
}