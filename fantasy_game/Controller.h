#pragma once
#include <future>
#include "Input.h"

const short allowableInputs = 8;

class Controller {
	private:
		bool inputs[allowableInputs];
		bool lockedInputs[allowableInputs];
		bool running;
		std::future<void> controllerTaskHandle;
		std::future<void> delayHandle;
		bool locked = false;
		int delayInMs;

		void ControlEngine();

		void delayAnInput(Input& inputType, int& milliseconds);

	public:
		Controller();

		void listen();

		void stopListening();

		bool checkInput(Input inputType);

		void lock();

		void unlock();

		void delayInput(int milliseconds);

		void lockInput(Input inputType);

		void unlockInput(Input inputType);

		void delaySpecificInput(Input inputType, int milliseconds);
};