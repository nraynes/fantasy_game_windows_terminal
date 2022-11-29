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
			Point pixel;
			int x = 30;
			int y = 15;
			pixel.value = '0';
			while (running) {
				Input command = controller.getInput();
				if (command == Input::LEFT && x > 0) {
					x--;
				}
				else if (command == Input::RIGHT && x < 60) {
					x++;
				}
				else if (command == Input::UP && y > 0) {
					y--;
				}
				else if (command == Input::DOWN && y < 30) {
					y++;
				}
				Sleep(100);
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