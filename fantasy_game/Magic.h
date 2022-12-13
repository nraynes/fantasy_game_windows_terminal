#pragma once
#include <string>
#include "Field.h"
#include "Object.h"

class Magic : public GameObject {
	protected:
		short spellID;
		std::string type;

	public:
		int value;

		Magic(short new_id, Field& i_field, short i_ID, int x = 0, int y = 0);

		short id();
};