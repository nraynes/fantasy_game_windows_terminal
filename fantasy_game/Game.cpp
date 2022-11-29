#include <future>
#include "Field.cpp"
#include "Controller.cpp"

class Game {
	private:
		bool running;
		int g_UPS;	// Global updates per second (Game Loop).
		std::future<void> gameTaskHandle;

	public:
		Game() : running(false), g_UPS(120) {}

		void play(Field& field, Controller& controller, bool& engineRunning) {
			running = true;
			Point pixel;
			int x = 30;
			int y = 15;
			pixel.value = '0';
			while (running) {
				Input command = controller.getInput();
				if (command == Input::LEFT && x > 0) {
					x--;
					controller.delaySpecificInput(Input::LEFT, 100);
				}
				else if (command == Input::RIGHT && x < field.width-1) {
					x++;
					controller.delaySpecificInput(Input::RIGHT, 100);
				}
				else if (command == Input::UP && y > 0) {
					y--;
					controller.delaySpecificInput(Input::UP, 100);
				}
				else if (command == Input::DOWN && y < field.height-1) {
					y++;
					controller.delaySpecificInput(Input::DOWN, 100);
				}
				else if (command == Input::CANCEL) {
					controller.lockInput(Input::RIGHT);
				}
				else if (command == Input::ACTION) {
					controller.unlockInput(Input::RIGHT);
				}
				Sleep(1000 / g_UPS);
				field.clear();
				field.matrix[y][x] = pixel;
			}
		}

		void start(Field& field, Controller& controller, bool& engineRunning) {
			gameTaskHandle = std::async(&Game::play, this, std::ref(field), std::ref(controller), std::ref(engineRunning));
		}
		
		void stop() {
			running = false;
			gameTaskHandle.get();
		}
};