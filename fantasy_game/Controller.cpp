#include <iostream>
#include <future>
#include <vector>
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
	NOINPUT,
};

static const short allowableInputs = 8;

class Controller {
	private:
		Input input = Input::NOINPUT;
		bool running = false;
		std::future<void> controllerTaskHandle;
		bool lockedInputs[allowableInputs]; // 8 is the number of allowable input controls excluding no input. If new inputs are added or some are removed, this number must change to reflect that.
		bool locked = false;
		int delayInMs = 0;

		void ControlEngine() {
			running = true;
			while (running) {
				if (locked) {
					input = Input::NOINPUT;
				} else if (GetKeyState(VK_UP) & 0x8000 && !lockedInputs[2]) {
					input = Input::UP;
				} else if (GetKeyState(VK_RIGHT) & 0x8000 && !lockedInputs[0]) {
					input = Input::RIGHT;
				} else if (GetKeyState(VK_LEFT) & 0x8000 && !lockedInputs[1]) {
					input = Input::LEFT;
				} else if (GetKeyState(VK_DOWN) & 0x8000 && !lockedInputs[3]) {
					input = Input::DOWN;
				} else if (GetKeyState('Z') & 0x8000 && !lockedInputs[4]) {
					input = Input::ACTION;
				} else if (GetKeyState('X') & 0x8000 && !lockedInputs[5]) {
					input = Input::CANCEL;
				} else if (GetKeyState('C') & 0x8000 && !lockedInputs[6]) {
					input = Input::SPECIAL;
				} else if (GetKeyState(VK_ESCAPE) & 0x8000 && !lockedInputs[7]) {
					input = Input::ESCAPE;
				} else {
					input = Input::NOINPUT;
				}
				if (delayInMs > 0) {
					input = Input::NOINPUT;
					Sleep(delayInMs);
					delayInMs = 0;
				}
			}
		}

		void delayAnInput(Input& inputType, int& milliseconds) {
			bool* tempHandle = nullptr;
			switch (inputType) {
				case Input::RIGHT:
					tempHandle = &lockedInputs[0];
					break;
				case Input::LEFT:
					tempHandle = &lockedInputs[1];
					break;
				case Input::UP:
					tempHandle = &lockedInputs[2];
					break;
				case Input::DOWN:
					tempHandle = &lockedInputs[3];
					break;
				case Input::ACTION:
					tempHandle = &lockedInputs[4];
					break;
				case Input::CANCEL:
					tempHandle = &lockedInputs[5];
					break;
				case Input::SPECIAL:
					tempHandle = &lockedInputs[6];
					break;
				case Input::ESCAPE:
					tempHandle = &lockedInputs[7];
					break;
				default:
					break;
			}
			*tempHandle = true;
			Sleep(milliseconds);
			*tempHandle = false;
		}

	public:
		void listen() {
			controllerTaskHandle = std::async(&Controller::ControlEngine, this);
		}

		void stopListening() {
			running = false;
			controllerTaskHandle.get();
		}

		Input getInput() {
			return input;
		}

		void lock() {
			locked = true;
		}

		void unlock() {
			locked = false;
			for (int i = 0; i < allowableInputs; i++) {
				lockedInputs[i] = false;
			}
		}

		void delayInput(int milliseconds) {
			delayInMs = milliseconds;
		}

		void lockInput(Input inputType) {
			switch (inputType) {
				case Input::RIGHT:
					lockedInputs[0] = true;
					break;
				case Input::LEFT:
					lockedInputs[1] = true;
					break;
				case Input::UP:
					lockedInputs[2] = true;
					break;
				case Input::DOWN:
					lockedInputs[3] = true;
					break;
				case Input::ACTION:
					lockedInputs[4] = true;
					break;
				case Input::CANCEL:
					lockedInputs[5] = true;
					break;
				case Input::SPECIAL:
					lockedInputs[6] = true;
					break;
				case Input::ESCAPE:
					lockedInputs[7] = true;
					break;
				default:
					break;
			}
		}

		void unlockInput(Input inputType) {
			switch (inputType) {
				case Input::RIGHT:
					lockedInputs[0] = false;
					break;
				case Input::LEFT:
					lockedInputs[1] = false;
					break;
				case Input::UP:
					lockedInputs[2] = false;
					break;
				case Input::DOWN:
					lockedInputs[3] = false;
					break;
				case Input::ACTION:
					lockedInputs[4] = false;
					break;
				case Input::CANCEL:
					lockedInputs[5] = false;
					break;
				case Input::SPECIAL:
					lockedInputs[6] = false;
					break;
				case Input::ESCAPE:
					lockedInputs[7] = false;
					break;
				default:
					break;
			}
		}

		void delaySpecificInput(Input inputType, int milliseconds) {
			std::future<void> asyncHandle = std::async(&Controller::delayAnInput, this, std::ref(inputType), std::ref(milliseconds));
		}
};