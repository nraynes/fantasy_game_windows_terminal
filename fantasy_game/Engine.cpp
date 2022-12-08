#include <iostream>
#include <Windows.h>
#include <WinUser.h>
#include "Engine.h"


GameEngine::GameEngine() : running(false) {};

void GameEngine::debug(std::string message) {
	std::wstring stemp = std::wstring(message.begin(), message.end());
	LPCWSTR sw = stemp.c_str();
	MessageBox(
		NULL,
		sw,
		(LPCWSTR)L"Game Engine Debug Message",
		MB_ICONINFORMATION | MB_OK | MB_DEFBUTTON1
	);
}

void GameEngine::start(Controller& controller, Screen& screen) {
	running = true;
	std::unique_ptr<Field> playingField(new Field);
	game.start(*playingField, controller, screen, std::bind(&GameEngine::stop, this));
	screen.start(*playingField); // This will allow the screen to run parallel to the game loop. Use screen.pause or screen.resume to control screen updates.
	controller.listen();
	while (running) {
		if (controller.checkInput(Input::ESCAPE)) {
			if (game.isPaused()) {
				game.unpause();
			} else {
				game.pause();
			}
		}
	}
	controller.stopListening();
	screen.stop();
	game.stop();
	std::cout << "\nGame Engine stopped...\n";
}

void GameEngine::stop() {
	running = false;
}