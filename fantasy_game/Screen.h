#pragma once
#include <future>
#include <string>
#include "Windows.h"
#include "Field.h"

class Screen {
	private:
		int FPS;
		HANDLE hOut;
		std::string output;
		std::future<void> screenTaskHandle;
		bool watching;
		bool hold;

	public:
		Screen();

		void hideCursor();

		void clearscreen();

		void render(Field& field);

		void pause();

		void resume();

		void watch(Field& field);

		void start(Field& field);

		void stop();
};