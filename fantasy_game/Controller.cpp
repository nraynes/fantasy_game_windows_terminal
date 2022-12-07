#include <iostream>
#include <vector>
#include <atomic>
#include <Windows.h>
#include <WinUser.h>
#include "Controller.h"

void Controller::checkKey(int key, short index) {
	if (GetKeyState(key) & 0x8000 && !lockedInputs[index]) {
		inputs[index] = true;
	} else {
		inputs[index] = false;
	}
}

void Controller::debug(std::string message) {
	std::wstring stemp = std::wstring(message.begin(), message.end());
	LPCWSTR sw = stemp.c_str();
	MessageBox(
		NULL,
		sw,
		(LPCWSTR)L"Controller Debug Message",
		MB_ICONINFORMATION | MB_OK | MB_DEFBUTTON1
	);
}

void Controller::ControlEngine() {
	running = true;
	while (running) {
		if (!locked) {
			checkKey(VK_RIGHT, 0);
			checkKey(VK_LEFT, 1);
			checkKey(VK_UP, 2);
			checkKey(VK_DOWN, 3);
			checkKey('Z', 4);
			checkKey('X', 5);
			checkKey('C', 6);
			checkKey(VK_ESCAPE, 7);
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

void Controller::delayAnInput(std::atomic<int>& milliseconds, std::atomic<bool>& inputLockRef) {
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
	inputLockRef = false;
}

Controller::Controller() : running(false), locked(false), delayInMs(0) {
	for (int i = 0; i < allowableInputs; i++) {
		inputs[i] = false;
		lockedInputs[i] = false;
	}
}

void Controller::listen() {
	controllerTaskHandle = std::async(std::launch::async, &Controller::ControlEngine, this);
}

void Controller::stopListening() {
	running = false;
	controllerTaskHandle.get();
}

bool Controller::checkInput(Input inputType) {
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

void Controller::lock() {
	locked = true;
}

void Controller::unlock() {
	locked = false;
	for (int i = 0; i < allowableInputs; i++) {
		lockedInputs[i] = false;
	}
}

void Controller::delayInput(int milliseconds) {
	delayInMs = milliseconds;
}

void Controller::lockInput(Input inputType) {
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

void Controller::unlockInput(Input inputType) {
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

void Controller::delaySpecificInput(Input inputType, std::atomic<int> milliseconds) {
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
	if (!lockedInputs[index]) {
		lockedInputs[index] = true;
		delayHandle = std::async(std::launch::async, &Controller::delayAnInput, this, std::ref(milliseconds), std::ref(lockedInputs[index]));
	}
}