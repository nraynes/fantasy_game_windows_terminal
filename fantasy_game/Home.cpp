#include <memory>
#include "Home.h"
#include "Entity.h"
#include "Field.h"

Home::Home(Field& field) {
	std::string enemySprite = "00      00  00  00      00      00  00  00      00";
	Entity* enemy = new Entity(field, 2, 50, 23);
	Entity* enemyTwo = new Entity(field, 3, 20, 5);
	enemy->addSprite(5, 10, "default", enemySprite);
	enemy->setSprite("default");
	enemyTwo->addSprite(5, 10, "default", enemySprite);
	enemyTwo->setSprite("default");
	enemy->makeSolid();
	enemyTwo->makeSolid();
	add("enemy_one", enemy);
	add("enemy_two", enemyTwo);
}