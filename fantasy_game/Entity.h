#pragma once
#include "Field.h"
#include "Object.h"
#include "Object.cpp"

template<int H, int W>
class Entity : public GameObject<H, W> {
	protected:
		int health;
		int maxHealth;
		int mana;
		int maxMana;

	public:
		Entity(Field& i_field, short i_ID, int x = 0, int y = 0);

		short moveRight(int amount = 1);

		short moveLeft(int amount = 1);

		short moveUp(int amount = 1);

		short moveDown(int amount = 1);

		void takeDamage(int damage);

		bool isDead();

		int getHealth();

		void heal(int hitpoints);

		void maxHeal();

		void setMaxHealth(int hitpoints, bool healEntity = false);

		void useMana(int amount);

		bool isManaDepleted();

		int getMana();

		void giveMana(int amount);

		void giveMaxMana();

		void setMaxMana(int amount, bool restoreEntity = false);
};