#include "Entity.h"

Entity::Entity(Field& i_field, short i_ID, int x, int y) :
	GameObject(i_field, i_ID, x, y),
	health(100),
	maxHealth(100),
	mana(100),
	maxMana(100)
{}

short Entity::moveRight(int amount) {
	Coord thisAnchor = this->getAnchor();
	return this->setAnchor(thisAnchor.x + amount, thisAnchor.y);;
}

short Entity::moveLeft(int amount) {
	Coord thisAnchor = this->getAnchor();
	return this->setAnchor(thisAnchor.x - amount, thisAnchor.y);
}

short Entity::moveUp(int amount) {
	Coord thisAnchor = this->getAnchor();
	return this->setAnchor(thisAnchor.x, thisAnchor.y - amount);
}

short Entity::moveDown(int amount) {
	Coord thisAnchor = this->getAnchor();
	return this->setAnchor(thisAnchor.x, thisAnchor.y + amount);
}

void Entity::takeDamage(int damage) {
	int newHealthVal = health - damage;
	if (newHealthVal >= 0) {
		health = newHealthVal;
	} else {
		health = 0;
	}
}

bool Entity::isDead() {
	bool retVal = health <= 0;
	return retVal;
}

int Entity::getHealth() {
	return health;
}

void Entity::heal(int hitpoints) {
	if (health + hitpoints <= maxHealth) {
		health += hitpoints;
	} else {
		health = maxHealth;
	}
}

void Entity::maxHeal() {
	health = maxHealth;
}

void Entity::setMaxHealth(int hitpoints, bool healEntity) {
	maxHealth = hitpoints;
	if (healEntity || maxHealth < health) {
		health = maxHealth;
	}
}

void Entity::useMana(int amount) {
	if (mana - amount >= 0) {
		mana -= amount;
	} else {
		mana = 0;
	}
}

bool Entity::isManaDepleted() {
	return mana <= 0;
}

int Entity::getMana() {
	return mana;
}

void Entity::giveMana(int amount) {
	if (mana + amount <= maxMana) {
		mana += amount;
	} else {
		mana = maxMana;
	}
}

void Entity::giveMaxMana() {
	mana = maxMana;
}

void Entity::setMaxMana(int amount, bool restoreEntity) {
	maxMana = amount;
	if (restoreEntity || maxMana < mana) {
		mana = maxMana;
	}
}