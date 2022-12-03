#include <future>
#include "Controller.cpp"
#include "Entity.cpp"

class Game {
	private:
		bool running;
		int g_UPS;	// Global updates per second (Game Loop).
		std::future<void> gameTaskHandle;

	public:
		Game() : running(false), g_UPS(120) {}

		void play(Field& field, Controller& controller, bool& engineRunning) {
			// Global game state goes here.
			Entity<5, 10>* player = new Entity<5, 10>(field, 7, 23);
			int refresh = 1000 / g_UPS;
			std::string playerSprite = "   0000   000    000  0    0    000000  00      00";
			player->addSprite("default", playerSprite);
			player->setSprite("default");
			int delayVar = 10;
			while (running) {
				Input command = controller.getInput();
				// Object and Field updates go here.
				switch (command) {
					case Input::LEFT:
						player->moveLeft();
						controller.delaySpecificInput(Input::LEFT, delayVar);
						break;
					case Input::RIGHT:
						player->moveRight();
						controller.delaySpecificInput(Input::RIGHT, delayVar);
						break;
					case Input::UP:
						player->moveUp();
						controller.delaySpecificInput(Input::UP, delayVar);
						break;
					case Input::DOWN:
						player->moveDown();
						controller.delaySpecificInput(Input::DOWN, delayVar);
						break;
					case Input::ACTION:
						field.test();
						break;
				}
				field.clear();
				player->render();
				Sleep(refresh);
			}
		}

		void start(Field& field, Controller& controller, bool& engineRunning) {
			running = true;
			gameTaskHandle = std::async(&Game::play, this, std::ref(field), std::ref(controller), std::ref(engineRunning));
		}
		
		void stop() {
			running = false;
			gameTaskHandle.get();
		}
};