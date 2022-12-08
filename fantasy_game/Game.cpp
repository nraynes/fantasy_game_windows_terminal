#include <future>
#include <Windows.h>
#include <WinUser.h>
#include "Game.h"

// Common game functions.

Game::Game() : running(false), paused(false), gameSpeed(200) {}

void Game::start(Field& field, Controller& controller, Screen& screen, std::function<void()> stopEngine) {
	running = true;
	gameTaskHandle = std::async(std::launch::async, &Game::play, this, std::ref(field), std::ref(controller), std::ref(screen), stopEngine);
}

void Game::pause() {
	paused = true;
}

bool Game::isPaused() {
	return paused;
}

void Game::unpause() {
	paused = false;
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

void Game::m_delay(std::function<void()> callback, std::atomic<volatile int>& milliseconds) {
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
	callback();
}

void Game::delay(std::function<void()> callback, std::atomic<volatile int> milliseconds) {
	handles.push_back(std::async(std::launch::async, &Game::m_delay, this, callback, std::ref(milliseconds)));
}
