#include <iostream>
#include "Engine.h"
#include "Controller.h"
#include "Screen.h"

int main() {
	Screen screen;
	Controller controller;
	GameEngine engine;
	screen.hideCursor();
	engine.start(controller, screen);
	return 0;
}