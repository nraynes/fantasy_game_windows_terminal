#include <iostream>
#include <future>
#include <Windows.h>

enum class Input {
	LEFT,
	RIGHT,
	UP,
	DOWN,
	ACTION,
	CANCEL,
	SPECIAL,
	ESCAPE,
	NOINPUT
};

class Controller {
	private:
		Input input = Input::NOINPUT;
		bool running = false;
		std::future<void> controllerTaskHandle;

		static void ControlEngine(Input& input, bool& running) {
			running = true;
			while (running) {
				if (GetKeyState(VK_RIGHT) & 0x8000) {
					input = Input::RIGHT;
				} else if (GetKeyState(VK_LEFT) & 0x8000) {
					input = Input::LEFT;
				} else if (GetKeyState(VK_UP) & 0x8000) {
					input = Input::UP;
				} else if (GetKeyState(VK_DOWN) & 0x8000) {
					input = Input::DOWN;
				} else if (GetKeyState('Z') & 0x8000) {
					input = Input::ACTION;
				} else if (GetKeyState('X') & 0x8000) {
					input = Input::CANCEL;
				} else if (GetKeyState('C') & 0x8000) {
					input = Input::SPECIAL;
				} else if (GetKeyState(VK_ESCAPE) & 0x8000) {
					input = Input::ESCAPE;
				} else {
					input = Input::NOINPUT;
				}
			}
		}

	public:
		void listen() {
			controllerTaskHandle = std::async(ControlEngine, std::ref(input), std::ref(running));
		}

		void stopListening() {
			running = false;
			controllerTaskHandle.get();
		}

		Input getInput() {
			return input;
		}
};