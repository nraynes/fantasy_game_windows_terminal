#pragma once
#include <future>
#include <string>
#include "Windows.h"
#include "Field.h"

class Screen {
	private:
		HANDLE hOut;
		std::string output;
		std::future<void> screenTaskHandle;
		bool watching;
		bool hold;
		short debugFrame;


	public:
		Screen();

		void debug(std::string message);

		void hideCursor();

		void clearscreen();

		void render(Field& field);

		void pause();

		void resume();

		void watch(Field& field);

		void start(Field& field);

		void stop();
};