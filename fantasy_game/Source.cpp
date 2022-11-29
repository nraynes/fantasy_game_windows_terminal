#include <iostream>
#include "Engine.cpp"

int main() {
	Screen screen;
	Controller controller;
	GameEngine engine;
	screen.hideCursor();
	engine.start(controller, screen);
	return 0;
}