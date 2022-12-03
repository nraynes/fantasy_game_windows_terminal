#include <iostream>
#include <future>
#include <vector>
#include <Windows.h>

enum class Input {
	RIGHT,
	LEFT,
	UP,
	DOWN,
	ACTION,
	CANCEL,
	SPECIAL,
	ESCAPE,
};

static const short allowableInputs = 8;

class Controller {
	private:
		bool inputs[allowableInputs];
		bool lockedInputs[allowableInputs];
		bool running = false;
		std::future<void> controllerTaskHandle;
		std::future<void> delayHandle;
		bool locked = false;
		int delayInMs = 0;

		void ControlEngine() {
			running = true;
			while (running) {
				if (!locked) {
					if (GetKeyState(VK_RIGHT) & 0x8000 && !lockedInputs[0]) {
						inputs[0] = true;
					} else {
						inputs[0] = false;
					}
					if (GetKeyState(VK_LEFT) & 0x8000 && !lockedInputs[1]) {
						inputs[1] = true;
					} else {
						inputs[1] = false;
					}
					if (GetKeyState(VK_UP) & 0x8000 && !lockedInputs[2]) {
						inputs[2] = true;
					} else {
						inputs[2] = false;
					}
					if (GetKeyState(VK_DOWN) & 0x8000 && !lockedInputs[3]) {
						inputs[3] = true;
					} else {
						inputs[3] = false;
					}
					if (GetKeyState('Z') & 0x8000 && !lockedInputs[4]) {
						inputs[4] = true;
					} else {
						inputs[4] = false;
					}
					if (GetKeyState('X') & 0x8000 && !lockedInputs[5]) {
						inputs[5] = true;
					} else {
						inputs[5] = false;
					}
					if (GetKeyState('C') & 0x8000 && !lockedInputs[6]) {
						inputs[6] = true;
					} else {
						inputs[6] = false;
					}
					if (GetKeyState(VK_ESCAPE) & 0x8000 && !lockedInputs[7]) {
						inputs[7] = true;
					} else {
						inputs[7] = false;
					}
				}
				if (delayInMs > 0) {
					for (int i = 0; i < allowableInputs; i++) {
						inputs[i] = false;
					}
					std::this_thread::sleep_for(std::chrono::milliseconds(delayInMs));
					delayInMs = 0;
				}
			}
		}

		void delayAnInput(Input& inputType, int& milliseconds) {
			short index = 0;
			switch (inputType) {
				case Input::RIGHT:
					index = 0;
					break;
				case Input::LEFT:
					index = 1;
					break;
				case Input::UP:
					index = 2;
					break;
				case Input::DOWN:
					index = 3;
					break;
				case Input::ACTION:
					index = 4;
					break;
				case Input::CANCEL:
					index = 5;
					break;
				case Input::SPECIAL:
					index = 6;
					break;
				case Input::ESCAPE:
					index = 7;
					break;
				default:
					break;
			}
			lockedInputs[index] = true;
			std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
			lockedInputs[index] = false;
		}

	public:
		void listen() {
			controllerTaskHandle = std::async(std::launch::async, &Controller::ControlEngine, this);
		}

		void stopListening() {
			running = false;
			controllerTaskHandle.get();
		}

		bool checkInput(Input inputType) {
			switch (inputType) {
				case Input::RIGHT:
					return inputs[0];
				case Input::LEFT:
					return inputs[1];
				case Input::UP:
					return inputs[2];
				case Input::DOWN:
					return inputs[3];
				case Input::ACTION:
					return inputs[4];
				case Input::CANCEL:
					return inputs[5];
				case Input::SPECIAL:
					return inputs[6];
				case Input::ESCAPE:
					return inputs[7];
				default:
					return false;
			}
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
			delayHandle = std::async(std::launch::async, &Controller::delayAnInput, this, std::ref(inputType), std::ref(milliseconds));
		}
};