#pragma once
#include <future>
#include <atomic>
#include <string>
#include "Input.h"

const short allowableInputs = 8;

class Controller {
	private:
		std::atomic<bool> inputs[allowableInputs];
		std::atomic<bool> lockedInputs[allowableInputs];
		std::atomic<bool> running;
		std::future<void> controllerTaskHandle;
		std::future<void> delayHandle;
		std::atomic<bool> locked;
		std::atomic<int> delayInMs;

		void ControlEngine();

		void delayAnInput(std::atomic<int>& milliseconds, std::atomic<bool>& inputLockRef);

	public:
		Controller();

		void checkKey(int key, short index);

		void debug(std::string message);

		void listen();

		void stopListening();

		bool checkInput(Input inputType);

		void lock();

		void unlock();

		void delayInput(int milliseconds);

		void lockInput(Input inputType);

		void unlockInput(Input inputType);

		void delaySpecificInput(Input inputType, std::atomic<int> milliseconds);
};