#include <future>
#include ".\Field.cpp"
#include ".\Controller.cpp"

class Game {
	private:
		bool running;
		std::future<void> gameTaskHandle;

	public:
		Game() : running(false) {}

		void play(Field& field, Controller& controller, bool& engineRunning) {
			running = true;
			while (running) {
				int x = rand() % 59;
				int y = rand() % 29;
				Point pixel;
				pixel.location.x = x;
				pixel.location.y = y;
				pixel.value = '0';
				Input command = controller.getInput();
				if (command == Input::ACTION) {
					x = 10;
					y = 10;
					pixel.location.x = x;
					pixel.location.y = y;
				} else if (command == Input::CANCEL) {
					engineRunning = false;
				}
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