#include "Game.h"
#include "Entity.h"
#include "Entity.cpp"
#include "Engine.h"

void Game::play(Field& field, Controller& controller, Screen& screen, GameEngine* engine) {
	// Global game state goes here.
	std::unique_ptr<Entity<5, 10>> player(new Entity<5, 10>(field, 1, 7, 23));
	std::unique_ptr<Entity<5, 10>> enemy(new Entity<5, 10>(field, 2, 50, 23));
	std::unique_ptr<Entity<5, 10>> enemyTwo(new Entity<5, 10>(field, 3, 20, 5));
	int refresh = 1000 / gameSpeed;
	std::string playerSprite = "   0000   000    000  0    0    000000  00      00";
	std::string playerHitSprite = "  000000  00      000        0 00000000 00      00";
	std::string enemySprite = "00      00  00  00      00      00  00  00      00";
	player->addSprite("default", playerSprite);
	player->addSprite("hit", playerHitSprite);
	player->setSprite("default");
	enemy->addSprite("default", enemySprite);
	enemy->setSprite("default");
	enemyTwo->addSprite("default", enemySprite);
	enemyTwo->setSprite("default");
	enemy->makeSolid();
	enemyTwo->makeSolid();
	player->makeSolid();
	int delayVar = 30;
	int hitTimer = 30;
	int counter = 0;
	bool wasHit = false;
	bool invincible = false;
	while (running) {
		while (paused) {}
		// Object and Field updates go here.
		if (controller.checkInput(Input::LEFT) && !controller.checkInput(Input::RIGHT)) {
			short collision = player->moveLeft();
			if (collision == 2 || collision == 3) {
				if (!invincible) {
					wasHit = true;
					invincible = true;
				}
			}
			controller.delaySpecificInput(Input::LEFT, delayVar);
		}
		if (controller.checkInput(Input::RIGHT) && !controller.checkInput(Input::LEFT)) {
			short collision = player->moveRight();
			if (collision == 2 || collision == 3) {
				if (!invincible) {
					wasHit = true;
					invincible = true;
				}
			}
			controller.delaySpecificInput(Input::RIGHT, delayVar);
		}
		if (controller.checkInput(Input::DOWN) && !controller.checkInput(Input::UP)) {
			short collision = player->moveDown();
			if (collision == 2 || collision == 3) {
				if (!invincible) {
					wasHit = true;
					invincible = true;
				}
			}
			controller.delaySpecificInput(Input::DOWN, delayVar);
		}
		if (controller.checkInput(Input::UP) && !controller.checkInput(Input::DOWN)) {
			short collision = player->moveUp();
			if (collision == 2 || collision == 3) {
				if (!invincible) {
					wasHit = true;
					invincible = true;
				}
			}
			controller.delaySpecificInput(Input::UP, delayVar);
		}
		if (player->isDead()) {
			debug("You are dead!");
			engine->stop();
		}
		if (wasHit) {
			player->takeDamage(5);
			player->setSprite("hit");
			delay([&invincible]() {invincible = false;}, 500);
			delay([&player]() {player->setSprite("default");}, 150);
			wasHit = false;
		}
		screen.pause();
		field.clear();
		enemy->render();
		enemyTwo->render();
		player->render();
		screen.resume();
		std::this_thread::sleep_for(std::chrono::milliseconds(refresh));
	}
}