#include "stdafx.h"

Character::Character()
{
	stat.hp = 0;
	stat.def = 0;
	stat.atk = 0;
	col = new ObRect();
	col->pivot = OFFSET_B;
	col->isFilled = false;

	for (int i = 0; i < 10; i++) {
		blockCol[i].scale = Vector2(16.0f, 16.0f);
		blockCol[i].isFilled = false;
	}
}

Character::~Character()
{
	SafeDelete(col);
}

void Character::Spawn()
{
	Vector2 pos = Vector2(0.0f, 1350.0f);
	Int2 intpos;
	tileMap->WorldPosToTileIdx(pos, intpos);
	while (true) {
		intpos.y--;
		if (tileMap->GetTileState(intpos) == TILE_WALL) {
			intpos = Int2(tileMap->tileSize.x * 0.5 - intpos.x, tileMap->tileSize.y * 0.5 - intpos.y);
			pos = Vector2(intpos.x * tileMap->scale.x, intpos.y * tileMap->scale.y);
			pos *= -1;
			pos.y += tileMap->scale.y + 1;
			col->SetWorldPos(pos);
			break;
		}
	}
}

void Character::Spawn(Vector2 playerPos)
{
	Vector2 pos = playerPos;
}

void Character::IsBlockUpdate()
{
	if (tileMap != nullptr) {
		Int2 tilePos;
		Vector2 pos;
		Vector2 debugPos;

		pos = col->GetWorldPos() - Vector2(col->scale.x * 0.5f, 0.0f);
		pos.x--;
		tileMap->WorldPosToTileIdx(pos, tilePos);
		
		debugPos = Vector2((tileMap->GetTileSize().x * 0.5f - tilePos.x) * tileMap->scale.x,
			(tileMap->GetTileSize().y * 0.5f - tilePos.y) * tileMap->scale.y);
		debugPos *= -1;
		debugPos += Vector2(tileMap->scale.x * 0.5f, tileMap->scale.y * 0.5f);

		blockCol[0].SetWorldPos(debugPos);
		if (tileMap->GetTileState(tilePos)) isCheckBlock[LEFT_1] = true;
		else isCheckBlock[LEFT_1] = false;
		tilePos.y++;

		debugPos = Vector2((tileMap->GetTileSize().x * 0.5f - tilePos.x) * tileMap->scale.x,
			(tileMap->GetTileSize().y * 0.5f - tilePos.y) * tileMap->scale.y);
		debugPos *= -1;
		debugPos += Vector2(tileMap->scale.x * 0.5f, tileMap->scale.y * 0.5f);

		blockCol[1].SetWorldPos(debugPos);
		if (tileMap->GetTileState(tilePos)) isCheckBlock[LEFT_2] = true;
		else isCheckBlock[LEFT_2] = false;
		tilePos.y++;

		debugPos = Vector2((tileMap->GetTileSize().x * 0.5f - tilePos.x) * tileMap->scale.x,
			(tileMap->GetTileSize().y * 0.5f - tilePos.y) * tileMap->scale.y);
		debugPos *= -1;
		debugPos += Vector2(tileMap->scale.x * 0.5f, tileMap->scale.y * 0.5f);

		blockCol[2].SetWorldPos(debugPos);
		if (tileMap->GetTileState(tilePos)) isCheckBlock[LEFT_3] = true;
		else isCheckBlock[LEFT_3] = false;

		pos = col->GetWorldPos() - Vector2(col->scale.x * 0.5f, 0.0f);
		pos.x++;
		pos.y--;
		tileMap->WorldPosToTileIdx(pos, tilePos);

		debugPos = Vector2((tileMap->GetTileSize().x * 0.5f - tilePos.x) * tileMap->scale.x,
			(tileMap->GetTileSize().y * 0.5f - tilePos.y) * tileMap->scale.y);
		debugPos *= -1;
		debugPos += Vector2(tileMap->scale.x * 0.5f, tileMap->scale.y * 0.5f);

		blockCol[3].SetWorldPos(debugPos);
		if (tileMap->GetTileState(tilePos)) isCheckBlock[DOWN_L] = true;
		else isCheckBlock[DOWN_L] = false;
		pos.y += col->scale.y + 1;
		tileMap->WorldPosToTileIdx(pos, tilePos);

		debugPos = Vector2((tileMap->GetTileSize().x * 0.5f - tilePos.x) * tileMap->scale.x,
			(tileMap->GetTileSize().y * 0.5f - tilePos.y) * tileMap->scale.y);
		debugPos *= -1;
		debugPos += Vector2(tileMap->scale.x * 0.5f, tileMap->scale.y * 0.5f);

		blockCol[4].SetWorldPos(debugPos);
		if (tileMap->GetTileState(tilePos)) isCheckBlock[UP_L] = true;
		else isCheckBlock[UP_L] = false;


		pos = col->GetWorldPos() + Vector2(col->scale.x * 0.5f, 0.0f);
		pos.x++;
		tileMap->WorldPosToTileIdx(pos, tilePos);

		debugPos = Vector2((tileMap->GetTileSize().x * 0.5f - tilePos.x) * tileMap->scale.x,
			(tileMap->GetTileSize().y * 0.5f - tilePos.y) * tileMap->scale.y);
		debugPos *= -1;
		debugPos += Vector2(tileMap->scale.x * 0.5f, tileMap->scale.y * 0.5f);

		blockCol[5].SetWorldPos(debugPos);
		if (tileMap->GetTileState(tilePos)) isCheckBlock[RIGHT_1] = true;
		else isCheckBlock[RIGHT_1] = false;
		tilePos.y++;

		debugPos = Vector2((tileMap->GetTileSize().x * 0.5f - tilePos.x) * tileMap->scale.x,
			(tileMap->GetTileSize().y * 0.5f - tilePos.y) * tileMap->scale.y);
		debugPos *= -1;
		debugPos += Vector2(tileMap->scale.x * 0.5f, tileMap->scale.y * 0.5f);

		blockCol[6].SetWorldPos(debugPos);
		if (tileMap->GetTileState(tilePos)) isCheckBlock[RIGHT_2] = true;
		else isCheckBlock[RIGHT_2] = false;
		tilePos.y++;

		debugPos = Vector2((tileMap->GetTileSize().x * 0.5f - tilePos.x) * tileMap->scale.x,
			(tileMap->GetTileSize().y * 0.5f - tilePos.y) * tileMap->scale.y);
		debugPos *= -1;
		debugPos += Vector2(tileMap->scale.x * 0.5f, tileMap->scale.y * 0.5f);

		blockCol[7].SetWorldPos(debugPos);
		if (tileMap->GetTileState(tilePos)) isCheckBlock[RIGHT_3] = true;
		else isCheckBlock[RIGHT_3] = false;
		pos = col->GetWorldPos() + Vector2(col->scale.x * 0.5f, 0.0f);
		pos.x--;
		pos.y--;
		tileMap->WorldPosToTileIdx(pos, tilePos);

		debugPos = Vector2((tileMap->GetTileSize().x * 0.5f - tilePos.x) * tileMap->scale.x,
			(tileMap->GetTileSize().y * 0.5f - tilePos.y) * tileMap->scale.y);
		debugPos *= -1;
		debugPos += Vector2(tileMap->scale.x * 0.5f, tileMap->scale.y * 0.5f);

		blockCol[8].SetWorldPos(debugPos);
		if (tileMap->GetTileState(tilePos)) isCheckBlock[DOWN_R] = true;
		else isCheckBlock[DOWN_R] = false;
		pos.y += col->scale.y + 1;
		tileMap->WorldPosToTileIdx(pos, tilePos);

		debugPos = Vector2((tileMap->GetTileSize().x * 0.5f - tilePos.x) * tileMap->scale.x,
			(tileMap->GetTileSize().y * 0.5f - tilePos.y) * tileMap->scale.y);
		debugPos *= -1;
		debugPos += Vector2(tileMap->scale.x * 0.5f, tileMap->scale.y * 0.5f);

		blockCol[9].SetWorldPos(debugPos);
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
	for (int i = 0; i < 10; i++) {
		blockCol[i].Update();
	}
}

void Character::LateUpdate()
{
	
}

void Character::Render()
{
	/*for (int i = 0; i < 10; i++) {
		blockCol[i].Render();
	}*/
}
