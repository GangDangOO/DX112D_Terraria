#include "stdafx.h"

Character::Character()
{
	stat.hp = 0;
	stat.def = 0;
	stat.atk = 0;
	col = new ObRect();
	col->pivot = OFFSET_B;
	col->isFilled = false;
}

Character::~Character()
{
	SafeDelete(col);
}
