#include <future>
#include "Controller.cpp"
#include "Entity.cpp"

class Game {
	private:
		bool running;
		int g_UPS;	// Global updates per second (Game Loop).
		std::future<void> gameTaskHandle;
		std::future<void> delayHandle;

	public:
		Game() : running(false), g_UPS(120) {}

		void delayMortality(bool& marker) {
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			marker = false;
		}

		void play(Field& field, Controller& controller, bool& engineRunning) {
			// Global game state goes here.
			Entity<5, 10>* player = new Entity<5, 10>(field, 7, 23);
			Entity<5, 10>* enemy = new Entity<5, 10>(field, 50, 23);
			int refresh = 1000 / g_UPS;
			short playerID = 1;
			short enemyID = 2;
			std::string playerSprite = "   0000   000    000  0    0    000000  00      00";
			std::string enemySprite = "00      00  00  00      00      00  00  00      00";
			player->setID(playerID);
			player->addSprite("default", playerSprite);
			player->setSprite("default");
			enemy->setID(enemyID);
			enemy->addSprite("default", enemySprite);
			enemy->setSprite("default");
			enemy->makeSolid();
			player->makeSolid();
			int delayVar = 30;
			int hitTimer = 30;
			bool wasHit = false;
			bool invincible = false;
			while (running) {
				// Object and Field updates go here.
				if (wasHit) {
					player->takeDamage(5);
					field.fill(hitTimer);
					wasHit = false;
				}
				if (controller.checkInput(Input::LEFT) && !controller.checkInput(Input::RIGHT)) {
					short collision = player->moveLeft();
					if (collision == 2) {
						if (!invincible) {
							wasHit = true;
							invincible = true;
							delayHandle = std::async(std::launch::async, &Game::delayMortality, this, std::ref(invincible));
						}
					}
					controller.delaySpecificInput(Input::LEFT, delayVar);
				}
				if (controller.checkInput(Input::RIGHT) && !controller.checkInput(Input::LEFT)) {
					short collision = player->moveRight();
					if (collision == 2) {
						if (!invincible) {
							wasHit = true;
							invincible = true;
							delayHandle = std::async(std::launch::async, &Game::delayMortality, this, std::ref(invincible));
						}
					}
					controller.delaySpecificInput(Input::RIGHT, delayVar);
				}
				if (controller.checkInput(Input::UP) && !controller.checkInput(Input::DOWN)) {
					short collision = player->moveUp();
					if (collision == 2) {
						if (!invincible) {
							wasHit = true;
							invincible = true;
							delayHandle = std::async(std::launch::async, &Game::delayMortality, this, std::ref(invincible));
						}
					}
					controller.delaySpecificInput(Input::UP, delayVar);
				}
				if (controller.checkInput(Input::DOWN) && !controller.checkInput(Input::UP)) {
					short collision = player->moveDown();
					if (collision == 2) {
						if (!invincible) {
							wasHit = true;
							invincible = true;
							delayHandle = std::async(std::launch::async, &Game::delayMortality, this, std::ref(invincible));
						}
					}
					controller.delaySpecificInput(Input::DOWN, delayVar);
				}
				if (player->isDead()) {
					engineRunning = false;
				}
				field.clear();
				enemy->render();
				player->render();
				std::this_thread::sleep_for(std::chrono::milliseconds(refresh));
			}
			delete player;
			delete enemy;
		}

		void start(Field& field, Controller& controller, bool& engineRunning) {
			running = true;
			gameTaskHandle = std::async(std::launch::async, &Game::play, this, std::ref(field), std::ref(controller), std::ref(engineRunning));
		}
		
		void stop() {
			running = false;
			gameTaskHandle.get();
		}
};