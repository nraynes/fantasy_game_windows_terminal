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
			Entity<5, 5>* player = new Entity<5, 5>(field, 7, 7);
			std::string playerSprite = "--0---0-0-0---0-0-0---0--";
			player->addSprite("default", playerSprite);
			player->setSprite("default");
			while (running) {
				Input command = controller.getInput();
				// Object and Field updates go here.
				switch (command) {
					case Input::LEFT:
						player->moveLeft();
						controller.delaySpecificInput(Input::LEFT, 50);
						break;
					case Input::RIGHT:
						player->moveRight();
						controller.delaySpecificInput(Input::RIGHT, 50);
						break;
					case Input::UP:
						player->moveUp();
						controller.delaySpecificInput(Input::UP, 50);
						break;
					case Input::DOWN:
						player->moveDown();
						controller.delaySpecificInput(Input::DOWN, 50);
						break;
					case Input::ACTION:
						field.test();
						break;
				}
				field.clear();
				player->render();
				Sleep(1000 / g_UPS);
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