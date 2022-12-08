#pragma once
#include <future>
#include <string>
#include <vector>
#include <atomic>
#include "Field.h"
#include "Controller.h"
#include "Screen.h"

class Game {
	private:
		bool running;
		const int gameSpeed;
		std::future<void> gameTaskHandle;
		std::vector<std::future<void>> handles;
		std::atomic<bool> paused;

		void m_delay(std::function<void()> callback, std::atomic<volatile int>& milliseconds);

	public:
		Game();

		void play(Field& field, Controller& controller, Screen& screen, std::function<void()> stopEngine);

		void debug(std::string message);

		void start(Field& field, Controller& controller, Screen& screen, std::function<void()> stopEngine);

		void pause();

		bool isPaused();

		void unpause();

		void stop();

		void delay(std::function<void()> callback, std::atomic<volatile int> milliseconds);
};