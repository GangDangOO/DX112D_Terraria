#include "stdafx.h"

Character::Character()
{
	stat.hp = 0;
	stat.def = 0;
	stat.atk = 0;
	col = new ObRect();
	col->pivot = OFFSET_B;
	col->isFilled = false;

	for (int i = 0; i < 8; i++) {
		blockCol[i].scale = Vector2(16.0f, 16.0f) * GAMESIZE;
		blockCol[i].isFilled = false;
	}
	invincibilityTime = 0.0f;
	respawnTime = 0.0f;
	isDead = false;
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
	pos.y += 500.0f;
	int r = RANDOM->Int(0, 1);
	int x = RANDOM->Int(0, 10);
	if (r == 0) {
		pos.x -= App.GetHalfWidth() + 100.0f;
	}
	else {
		pos.x += App.GetHalfWidth() + 100.0f;
	}
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

		blockCol[LEFT_D].SetWorldPos(debugPos);
		if (tileMap->GetTileState(tilePos)) isCheckBlock[LEFT_D] = true;
		else isCheckBlock[LEFT_D] = false;
		tilePos.y++;


		debugPos = Vector2((tileMap->GetTileSize().x * 0.5f - tilePos.x) * tileMap->scale.x,
			(tileMap->GetTileSize().y * 0.5f - tilePos.y) * tileMap->scale.y);
		debugPos *= -1;
		debugPos += Vector2(tileMap->scale.x * 0.5f, tileMap->scale.y * 0.5f);

		blockCol[LEFT_U].SetWorldPos(debugPos);
		if (tileMap->GetTileState(tilePos)) isCheckBlock[LEFT_U] = true;
		else isCheckBlock[LEFT_U] = false;

		pos = col->GetWorldPos() - Vector2(col->scale.x * 0.5f, 0.0f);
		pos.x++;
		pos.y--;
		tileMap->WorldPosToTileIdx(pos, tilePos);

		debugPos = Vector2((tileMap->GetTileSize().x * 0.5f - tilePos.x) * tileMap->scale.x,
			(tileMap->GetTileSize().y * 0.5f - tilePos.y) * tileMap->scale.y);
		debugPos *= -1;
		debugPos += Vector2(tileMap->scale.x * 0.5f, tileMap->scale.y * 0.5f);

		blockCol[DOWN_L].SetWorldPos(debugPos);
		if (tileMap->GetTileState(tilePos)) isCheckBlock[DOWN_L] = true;
		else isCheckBlock[DOWN_L] = false;
		pos.y += col->scale.y + 1;
		tileMap->WorldPosToTileIdx(pos, tilePos);

		debugPos = Vector2((tileMap->GetTileSize().x * 0.5f - tilePos.x) * tileMap->scale.x,
			(tileMap->GetTileSize().y * 0.5f - tilePos.y) * tileMap->scale.y);
		debugPos *= -1;
		debugPos += Vector2(tileMap->scale.x * 0.5f, tileMap->scale.y * 0.5f);

		blockCol[UP_L].SetWorldPos(debugPos);
		if (tileMap->GetTileState(tilePos)) isCheckBlock[UP_L] = true;
		else isCheckBlock[UP_L] = false;


		pos = col->GetWorldPos() + Vector2(col->scale.x * 0.5f, 0.0f);
		pos.x++;
		tileMap->WorldPosToTileIdx(pos, tilePos);

		debugPos = Vector2((tileMap->GetTileSize().x * 0.5f - tilePos.x) * tileMap->scale.x,
			(tileMap->GetTileSize().y * 0.5f - tilePos.y) * tileMap->scale.y);
		debugPos *= -1;
		debugPos += Vector2(tileMap->scale.x * 0.5f, tileMap->scale.y * 0.5f);

		blockCol[RIGHT_D].SetWorldPos(debugPos);
		if (tileMap->GetTileState(tilePos)) isCheckBlock[RIGHT_D] = true;
		else isCheckBlock[RIGHT_D] = false;
		tilePos.y++;

		debugPos = Vector2((tileMap->GetTileSize().x * 0.5f - tilePos.x) * tileMap->scale.x,
			(tileMap->GetTileSize().y * 0.5f - tilePos.y) * tileMap->scale.y);
		debugPos *= -1;
		debugPos += Vector2(tileMap->scale.x * 0.5f, tileMap->scale.y * 0.5f);

		blockCol[RIGHT_U].SetWorldPos(debugPos);
		if (tileMap->GetTileState(tilePos)) isCheckBlock[RIGHT_U] = true;
		else isCheckBlock[RIGHT_U] = false;
		pos = col->GetWorldPos() + Vector2(col->scale.x * 0.5f, 0.0f);
		pos.x--;
		pos.y--;
		tileMap->WorldPosToTileIdx(pos, tilePos);

		debugPos = Vector2((tileMap->GetTileSize().x * 0.5f - tilePos.x) * tileMap->scale.x,
			(tileMap->GetTileSize().y * 0.5f - tilePos.y) * tileMap->scale.y);
		debugPos *= -1;
		debugPos += Vector2(tileMap->scale.x * 0.5f, tileMap->scale.y * 0.5f);

		blockCol[DOWN_R].SetWorldPos(debugPos);
		if (tileMap->GetTileState(tilePos)) isCheckBlock[DOWN_R] = true;
		else isCheckBlock[DOWN_R] = false;
		pos.y += col->scale.y + 1;
		tileMap->WorldPosToTileIdx(pos, tilePos);

		debugPos = Vector2((tileMap->GetTileSize().x * 0.5f - tilePos.x) * tileMap->scale.x,
			(tileMap->GetTileSize().y * 0.5f - tilePos.y) * tileMap->scale.y);
		debugPos *= -1;
		debugPos += Vector2(tileMap->scale.x * 0.5f, tileMap->scale.y * 0.5f);

		blockCol[UP_R].SetWorldPos(debugPos);
		if (tileMap->GetTileState(tilePos)) isCheckBlock[UP_R] = true;
		else isCheckBlock[UP_R] = false;

		/*cout << "------------------------------\n";
		cout << ' ' << isCheckBlock[UP_L] << isCheckBlock[UP_R] << '\n';
		cout << isCheckBlock[LEFT_U] << "  " << isCheckBlock[RIGHT_U] << '\n';
		cout << isCheckBlock[LEFT_D] << "  " << isCheckBlock[RIGHT_D] << '\n';
		cout << ' ' << isCheckBlock[DOWN_L] << isCheckBlock[DOWN_R] << '\n';
		cout << "------------------------------\n";*/
		if (isCheckBlock[LEFT_D] || isCheckBlock[LEFT_U]) dirCheck.left = true;
		else dirCheck.left = false;
		if (isCheckBlock[RIGHT_D] || isCheckBlock[RIGHT_U]) dirCheck.right = true;
		else dirCheck.right = false;
		if (isCheckBlock[UP_L] || isCheckBlock[UP_R]) dirCheck.up = true;
		else dirCheck.up = false;
		if (isCheckBlock[DOWN_L] || isCheckBlock[DOWN_R]) {
			
			dirCheck.down = true;
		}
		else dirCheck.down = false;
		// cout << dirCheck.left << ' ' << dirCheck.right << ' ' << dirCheck.up << ' ' << dirCheck.down << '\n';
	}
}

void Character::Update()
{

	if (!isDead) {
		invincibilityTime -= DELTA;
		IsBlockUpdate();
		/*for (int i = 0; i < 8; i++) {
			blockCol[i].Update();
		}*/
	}
	else {
		respawnTime -= DELTA;
		for (int i = 0; i < 4; i++) {
			if (goreSprite[i] != nullptr) goreSprite[i]->Update();
		}
		Dead();
	}
}

void Character::LateUpdate()
{
	
}

void Character::Render()
{
	if (isDead) {
		for (int i = 0; i < 4; i++) {
			if (goreSprite[i] != nullptr) goreSprite[i]->Render();
		}
	}
	/*for (int i = 0; i < 8; i++) {
		blockCol[i].Render();
	}*/
}

void Character::Dead()
{
	for (int i = 0; i < 4; i++) {
		move.y -= 100 * DELTA;
		if (goreSprite[i] != nullptr) {
			Vector2 n;
			if (move.x < 0.0f) n = Vector2(i * -50, 100 + i * 50);
			else if (move.x > 0.0f) n = Vector2(i * 50, 100 + i * 50);
			goreSprite[i]->MoveWorldPos((move + n)* DELTA);
			goreSprite[i]->rotation += ToRadian * DELTA * 180;
		}
	}
}

void Character::Hit(Status enemyStat, Vector2 enemyCol)
{
	if (invincibilityTime <= 0.0f && !isDead) {
		int dmg = enemyStat.atk - stat.def;
		if (dmg <= 0) dmg = 1;
		stat.hp -= dmg;
		int knock = ((100 + dmg) - ((100 + dmg) * stat.knockBack)) * GAMESIZE;
		if (col->GetWorldPos().x < enemyCol.x) move.x -= knock * 2;
		else if (col->GetWorldPos().x > enemyCol.x) move.x += knock * 2;
		move.y += knock;
		if (stat.hp <= 0) {
			for (int i = 0; i < 4; i++) {
				move.y = 0.0f;
				if (goreSprite[i] != nullptr) {
					goreSprite[i]->SetWorldPos(col->GetWorldPos());
					goreSprite[i]->rotation = 0.0f;
				}
			}
			respawnTime = 7.0f;
			isDead = true;
		}
		invincibilityTime = 0.8f;
		cout << stat.hp << '\n';
	}
}
