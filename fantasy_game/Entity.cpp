#include "Object.cpp"

template<int H, int W>
class Entity : public GameObject<H, W> {
	private:
		int health;
		int maxHealth;
		int mana;
		int maxMana;

	public:
		Entity(Field& i_field, int x = 0, int y = 0) :
			GameObject<H, W>(i_field, x, y),
			health(100),
			maxHealth(100),
			mana(100),
			maxMana(100)
		{}

		short moveRight(int amount = 1) {
			short collision = this->sprite.checkCollision(*this->field, Coord(this->anchor.x + amount, this->anchor.y));
			if (!collision) {
				this->anchor.x += amount;
			}
			return collision;
		}

		short moveLeft(int amount = 1) {
			short collision = this->sprite.checkCollision(*this->field, Coord(this->anchor.x - amount, this->anchor.y));
			if (!collision) {
				this->anchor.x -= amount;
			}
			return collision;
		}

		short moveUp(int amount = 1) {
			short collision = this->sprite.checkCollision(*this->field, Coord(this->anchor.x, this->anchor.y - amount));
			if (!collision) {
				this->anchor.y -= amount;
			}
			return collision;
		}

		short moveDown(int amount = 1) {
			short collision = this->sprite.checkCollision(*this->field, Coord(this->anchor.x, this->anchor.y + amount));
			if (!collision) {
				this->anchor.y += amount;
			}
			return collision;
		}

		void takeDamage(int damage) {
			int newHealthVal = health - damage;
			if (newHealthVal >= 0) {
				health = newHealthVal;
			} else {
				health = 0;
			}
		}

		bool isDead() {
			bool retVal = health <= 0;
			return retVal;
		}

		int getHealth() {
			return health;
		}

		void heal(int hitpoints) {
			if (health + hitpoints <= maxHealth) {
				health += hitpoints;
			} else {
				health = maxHealth;
			}
		}

		void maxHeal() {
			health = maxHealth;
		}

		void setMaxHealth(int hitpoints, bool healEntity = false) {
			maxHealth = hitpoints;
			if (healEntity || maxHealth < health) {
				health = maxHealth;
			}
		}

		void useMana(int amount) {
			if (mana - amount >= 0) {
				mana -= amount;
			} else {
				mana = 0;
			}
		}

		bool isManaDepleted() {
			return mana <= 0;
		}

		int getMana() {
			return mana;
		}

		void giveMana(int amount) {
			if (mana + amount <= maxMana) {
				mana += amount;
			} else {
				mana = maxMana;
			}
		}

		void giveMaxMana() {
			mana = maxMana;
		}

		void setMaxMana(int amount, bool restoreEntity = false) {
			maxMana = amount;
			if (restoreEntity || maxMana < mana) {
				mana = maxMana;
			}
		}
};