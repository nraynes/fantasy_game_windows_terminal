#include "Game.h"
#include "Entity.h"
#include "Entity.cpp"

Game::Game() : running(false), g_UPS(200) {}

void Game::delayMortality(bool& marker) {
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	marker = false;
}

void Game::play(Field& field, Controller& controller, Screen& screen, bool& engineRunning) {
	// Global game state goes here.
	std::unique_ptr<Entity<5, 10>> player(new Entity<5, 10>(field, 1, 7, 23));
	std::unique_ptr<Entity<5, 10>> enemy(new Entity<5, 10>(field, 2, 50, 23));
	int refresh = 1000 / g_UPS;
	std::string playerSprite = "   0000   000    000  0    0    000000  00      00";
	std::string enemySprite = "00      00  00  00      00      00  00  00      00";
	player->addSprite("default", playerSprite);
	player->setSprite("default");
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
		if (controller.checkInput(Input::ACTION)) {
			player->setAnchorRelativeTo(2, 20, 0);
			controller.delaySpecificInput(Input::ACTION, 100);
		}
		if (player->isDead()) {
			engineRunning = false;
			field.fill(2000, "You are dead!           ");
		}
		screen.pause();
		field.clear();
		enemy->render();
		player->render();
		screen.resume();
		std::this_thread::sleep_for(std::chrono::milliseconds(refresh));
	}
}

void Game::start(Field& field, Controller& controller, Screen& screen, bool& engineRunning) {
	running = true;
	gameTaskHandle = std::async(std::launch::async, &Game::play, this, std::ref(field), std::ref(controller), std::ref(screen), std::ref(engineRunning));
}
		
void Game::stop() {
	running = false;
	gameTaskHandle.get();
}