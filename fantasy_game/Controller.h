#pragma once
#include <future>
#include <atomic>
#include <string>
#include "Input.h"

const short allowableInputs = 8;

class Controller {
	private:
		bool inputs[allowableInputs];
		bool lockedInputs[allowableInputs];
		bool running;
		std::future<void> controllerTaskHandle;
		std::future<void> delayHandle;
		bool locked;
		int delayInMs;

		void ControlEngine();

		void delayAnInput(std::atomic<int>& milliseconds, bool& inputLockRef);

	public:
		Controller();

		void checkKey(int key, short index);

		void debug(std::string message);

		void listen();

		void stopListening();

		bool checkInput(volatile Input inputType);

		void lock();

		void unlock();

		void delayInput(int milliseconds);

		void lockInput(volatile Input inputType);

		void unlockInput(volatile Input inputType);

		void delaySpecificInput(volatile Input inputType, std::atomic<int> milliseconds);
};