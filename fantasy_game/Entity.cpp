#include "Entity.h"

template<int H, int W>
Entity<H, W>::Entity(Field& i_field, short i_ID, int x, int y) :
	GameObject<H, W>(i_field, i_ID, x, y),
	health(100),
	maxHealth(100),
	mana(100),
	maxMana(100)
{}

template<int H, int W>
short Entity<H, W>::moveRight(int amount) {
	Coord thisAnchor = this->getAnchor();
	return this->setAnchor(thisAnchor.x + amount, thisAnchor.y);;
}

template<int H, int W>
short Entity<H, W>::moveLeft(int amount) {
	Coord thisAnchor = this->getAnchor();
	return this->setAnchor(thisAnchor.x - amount, thisAnchor.y);
}

template<int H, int W>
short Entity<H, W>::moveUp(int amount) {
	Coord thisAnchor = this->getAnchor();
	return this->setAnchor(thisAnchor.x, thisAnchor.y - amount);
}

template<int H, int W>
short Entity<H, W>::moveDown(int amount) {
	Coord thisAnchor = this->getAnchor();
	return this->setAnchor(thisAnchor.x, thisAnchor.y + amount);
}

template<int H, int W>
void Entity<H, W>::takeDamage(int damage) {
	int newHealthVal = health - damage;
	if (newHealthVal >= 0) {
		health = newHealthVal;
	} else {
		health = 0;
	}
}

template<int H, int W>
bool Entity<H, W>::isDead() {
	bool retVal = health <= 0;
	return retVal;
}

template<int H, int W>
int Entity<H, W>::getHealth() {
	return health;
}

template<int H, int W>
void Entity<H, W>::heal(int hitpoints) {
	if (health + hitpoints <= maxHealth) {
		health += hitpoints;
	} else {
		health = maxHealth;
	}
}

template<int H, int W>
void Entity<H, W>::maxHeal() {
	health = maxHealth;
}

template<int H, int W>
void Entity<H, W>::setMaxHealth(int hitpoints, bool healEntity) {
	maxHealth = hitpoints;
	if (healEntity || maxHealth < health) {
		health = maxHealth;
	}
}

template<int H, int W>
void Entity<H, W>::useMana(int amount) {
	if (mana - amount >= 0) {
		mana -= amount;
	} else {
		mana = 0;
	}
}

template<int H, int W>
bool Entity<H, W>::isManaDepleted() {
	return mana <= 0;
}

template<int H, int W>
int Entity<H, W>::getMana() {
	return mana;
}

template<int H, int W>
void Entity<H, W>::giveMana(int amount) {
	if (mana + amount <= maxMana) {
		mana += amount;
	} else {
		mana = maxMana;
	}
}

template<int H, int W>
void Entity<H, W>::giveMaxMana() {
	mana = maxMana;
}

template<int H, int W>
void Entity<H, W>::setMaxMana(int amount, bool restoreEntity) {
	maxMana = amount;
	if (restoreEntity || maxMana < mana) {
		mana = maxMana;
	}
}