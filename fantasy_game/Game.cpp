#include <Windows.h>
#include <WinUser.h>
#include "Game.h"

// Common game functions.

Game::Game() : running(false), g_UPS(200) {}

void Game::start(Field& field, Controller& controller, Screen& screen, std::function<void()> stopEngine) {
	running = true;
	gameTaskHandle = std::async(std::launch::async, &Game::play, this, std::ref(field), std::ref(controller), std::ref(screen), stopEngine);
}
		
void Game::stop() {
	running = false;
	gameTaskHandle.get();
}

void Game::debug(std::string message) {
	std::wstring stemp = std::wstring(message.begin(), message.end());
	LPCWSTR sw = stemp.c_str();
	MessageBox(
		NULL,
		sw,
		(LPCWSTR)L"Game Debug Message",
		MB_ICONINFORMATION | MB_OK | MB_DEFBUTTON1
	);
}