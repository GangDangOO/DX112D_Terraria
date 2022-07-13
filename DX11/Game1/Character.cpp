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

void Character::IsBlockUpdate()
{
	if (tileMap != nullptr) {
		Int2 tilePos;
		Vector2 pos;

		pos = col->GetWorldPos() - Vector2(col->scale.x * 0.5f, 0.0f);
		pos.x--;
		tileMap->WorldPosToTileIdx(pos, tilePos);
		tilePos.y++;
		if (tileMap->GetTileState(tilePos)) isCheckBlock[LEFT_1] = true;
		else isCheckBlock[LEFT_1] = false;
		tilePos.y++;
		if (tileMap->GetTileState(tilePos)) isCheckBlock[LEFT_2] = true;
		else isCheckBlock[LEFT_2] = false;
		tilePos.y++;
		if (tileMap->GetTileState(tilePos)) isCheckBlock[LEFT_3] = true;
		else isCheckBlock[LEFT_3] = false;

		pos = col->GetWorldPos() - Vector2(col->scale.x * 0.5f, 0.0f);
		pos.x++;
		tileMap->WorldPosToTileIdx(pos, tilePos);
		if (tileMap->GetTileState(tilePos)) isCheckBlock[DOWN_L] = true;
		else isCheckBlock[DOWN_L] = false;
		pos.y += col->scale.y;
		tileMap->WorldPosToTileIdx(pos, tilePos);
		if (tileMap->GetTileState(tilePos)) isCheckBlock[UP_L] = true;
		else isCheckBlock[UP_L] = false;


		pos = col->GetWorldPos() + Vector2(col->scale.x * 0.5f, 0.0f);
		pos.x++;
		tileMap->WorldPosToTileIdx(pos, tilePos);
		tilePos.y++;
		if (tileMap->GetTileState(tilePos)) isCheckBlock[RIGHT_1] = true;
		else isCheckBlock[RIGHT_1] = false;
		tilePos.y++;
		if (tileMap->GetTileState(tilePos)) isCheckBlock[RIGHT_2] = true;
		else isCheckBlock[RIGHT_2] = false;
		tilePos.y++;
		if (tileMap->GetTileState(tilePos)) isCheckBlock[RIGHT_3] = true;
		else isCheckBlock[RIGHT_3] = false;
		pos = col->GetWorldPos() + Vector2(col->scale.x * 0.5f, 0.0f);
		pos.x--;
		tileMap->WorldPosToTileIdx(pos, tilePos);
		if (tileMap->GetTileState(tilePos)) isCheckBlock[DOWN_R] = true;
		else isCheckBlock[DOWN_R] = false;
		pos.y += col->scale.y;
		tileMap->WorldPosToTileIdx(pos, tilePos);
		if (tileMap->GetTileState(tilePos)) isCheckBlock[UP_R] = true;
		else isCheckBlock[UP_R] = false;

		/*cout << "------------------------------\n";
		cout << ' ' << isCheckBlock[UP_L] << isCheckBlock[UP_R] << '\n';
		cout << isCheckBlock[LEFT_3] << "  " << isCheckBlock[RIGHT_3] << '\n';
		cout << isCheckBlock[LEFT_2] << "  " << isCheckBlock[RIGHT_2] << '\n';
		cout << isCheckBlock[LEFT_1] << "  " << isCheckBlock[RIGHT_1] << '\n';
		cout << ' ' << isCheckBlock[DOWN_L] << isCheckBlock[DOWN_R] << '\n';
		cout << "------------------------------\n";*/
		if (isCheckBlock[LEFT_1] || isCheckBlock[LEFT_2] || isCheckBlock[LEFT_3]) dirCheck.left = true;
		else dirCheck.left = false;
		if (isCheckBlock[RIGHT_1] || isCheckBlock[RIGHT_2] || isCheckBlock[RIGHT_3]) dirCheck.right = true;
		else dirCheck.right = false;
		if (isCheckBlock[UP_L] || isCheckBlock[UP_R]) dirCheck.up = true;
		else dirCheck.up = false;
		if (isCheckBlock[DOWN_L] || isCheckBlock[DOWN_R]) dirCheck.down = true;
		else dirCheck.down = false;
		// cout << dirCheck.left << ' ' << dirCheck.right << ' ' << dirCheck.up << ' ' << dirCheck.down << '\n';
	}
}

void Character::Update()
{
	IsBlockUpdate();
}
