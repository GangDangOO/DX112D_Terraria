#include "stdafx.h"

Map::Map(Int2 MapSize, unsigned int Seed)
{
	tileSize = MapSize;
	PerlinNoise pn(Seed);
	type = new byte * [tileSize.y];
	blockHp = new int* [tileSize.y];
	for (int i = 0; i < tileSize.y; i++) {
		type[i] = new byte[tileSize.x];
		blockHp[i] = new int[tileSize.x];
	}
	for (int i = 0; i < tileSize.y; ++i) {
		for (int j = 0; j < tileSize.x; ++j) {
			if (i < tileSize.y * 0.68) {
				double x = (double)j / ((double)tileSize.x);
				double y = (double)i / ((double)tileSize.y);

				double n = pn.noise(x * 500, y * 100, 0.7);

				if (n > 0.5f) {
					type[i][j] = AIR;
				}
				else {
					type[i][j] = DIRT;
				}
			}
			else {
				if (i > tileSize.y * 0.7) {
					type[i][j] = AIR;
				}
				else {
					double x = (double)j / ((double)tileSize.x);
					double y = (double)i / ((double)tileSize.y);

					double n = pn.noise(x * 200, y * 60, 0.8);
					if (n > 0.6) {
						type[i][j] = AIR;
					}
					else {
						type[i][j] = DIRT;
					}
				}
			}
		}
	}
	for (int i = 0; i < tileSize.y; ++i) {
		for (int j = 0; j < tileSize.x; ++j) {
			if (i < tileSize.y * 0.65) {
				double x = (double)j / ((double)tileSize.x);
				double y = (double)i / ((double)tileSize.y);

				double n = pn.noise(x * 500, y * 300, 0.7);

				if (n > 0.3f && type[i][j] == DIRT) {
					type[i][j] = ROCK;
				}
			}
		}
	}
	isRectVisible = false;
	CellularAutomata();
	CellularAutomata();
	CellularAutomata();
	for (int i = 0; i < tileSize.y; ++i) {
		for (int j = 0; j < tileSize.x; ++j) {
			switch (type[i][j])
			{
			case DIRT:
				blockHp[i][j] = 3;
				break;
			case GRASS:
				blockHp[i][j] = 3;
				break;
			case ROCK:
				blockHp[i][j] = 6;
				break;
			case TOUCH:
				blockHp[i][j] = 1;
				break;
			case FLOWER:
				break;
			default:
				blockHp[i][j] = 0;
				break;
			}
		}
	}

	for (int i = 0; i < 5; i++) {
		dirt[i] = new ObImage(L"Tiles_0.png");
		dirt[i]->maxFrame = Int2(16, 15);
		dirt[i]->frame = Int2(0, 5);
		dirt[i]->scale = Vector2(4, 4);

		rock[i] = new ObImage(L"Tiles_1.png");
		rock[i]->maxFrame = Int2(16, 15);
		rock[i]->frame = Int2(0, 5);
		rock[i]->scale = Vector2(4, 4);
	}
	visibleTime = 0.0f;
}

Map::~Map()
{
}

void Map::Release()
{
	for (int i = 0; i < tileSize.y; i++) {
		SafeDelete(type[i]);
		SafeDelete(blockHp[i]);
	}
	SafeDelete(type);
	SafeDelete(blockHp);
	for (int i = 0; i < 5; i++) {
		SafeDelete(dirt[i]);
		SafeDelete(rock[i]);
	}
}

void Map::Update()
{
	visibleTime -= DELTA;
	if (visibleTime < 0.0f) {
		if (dirt[0]->visible) {
			for (int i = 0; i < 5; i++) {
				dirt[i]->visible = false;
			}
		}
		if (rock[0]->visible) {
			for (int i = 0; i < 5; i++) {
				rock[i]->visible = false;
			}
		}
	}
	else {
		if (dirt[0]->visible) {
			for (int i = 0; i < 5; i++) {
				dirt[i]->MoveWorldPos(Vector2(-50 + i * 30, -50.0f) * DELTA);
			}
		}
		if (rock[0]->visible) {
			for (int i = 0; i < 5; i++) {
				rock[i]->MoveWorldPos(Vector2(-50 + i * 30, -50.0f) * DELTA);
			}
		}
	}
	if (INPUT->KeyDown('Q')) {
		isRectVisible = !isRectVisible;
	}
	for (int i = 0; i < 5; i++) {
		dirt[i]->Update();
		rock[i]->Update();
	}
}

void Map::LateUpdate()
{

}

void Map::Render()
{
	for (int i = 0; i < 5; i++) {
		dirt[i]->Render();
		rock[i]->Render();
	}
}

bool Map::MiningBlock(Int2 pos)
{
	bool isDelete = false;
	blockHp[pos.y][pos.x]--;
	if (type[pos.y][pos.x] == DIRT) {
		Int2 intpos;
		Vector2 blockPos = INPUT->GetMouseWorldPos();
		tileMap->WorldPosToTileIdx(blockPos, intpos);
		intpos = Int2(tileSize.x * 0.5 - intpos.x, tileSize.y * 0.5 - intpos.y);
		blockPos = Vector2(intpos.x * 16, intpos.y * 16);
		blockPos *= -1;
		blockPos.y += 8;
		for (int i = 0; i < 5; i++) {
			dirt[i]->SetWorldPos(blockPos);
			dirt[i]->Update();
			dirt[i]->visible = true;
			
		}
	}
	else if (type[pos.y][pos.x] == ROCK) {
		Int2 intpos;
		Vector2 blockPos = INPUT->GetMouseWorldPos();
		intpos = Int2(tileSize.x * 0.5 - intpos.x, tileSize.y * 0.5 - intpos.y);
		blockPos = Vector2(intpos.x * 16, intpos.y * 16);
		blockPos *= -1;
		blockPos.y += 8;
		for (int i = 0; i < 5; i++) {
			rock[i]->SetWorldPos(blockPos);
			rock[i]->Update();
			rock[i]->visible = true;
		}
	}
	visibleTime = 0.5f;
	if (blockHp[pos.y][pos.x] <= 0) isDelete = true;
	return isDelete;
}

void Map::CellularAutomata()
{
	for (int i = 1; i < tileSize.y - 1; ++i) {
		for (int j = 1; j < tileSize.x - 1; ++j) {
			if (type[i][j] == AIR) {
				int count = 0;
				if (type[i + 1][j - 1] != AIR) count++;
				if (type[i + 1][j] != AIR) count++;
				if (type[i + 1][j + 1] != AIR) count++;
				if (type[i][j - 1] != AIR) count++;
				if (type[i][j + 1] != AIR) count++;
				if (type[i - 1][j - 1] != AIR) count++;
				if (type[i - 1][j] != AIR) count++;
				if (type[i - 1][j + 1] != AIR) count++;
				if (count >= 5) {
					type[i][j] = DIRT;
				}
			}
		}
	}
}

void Map::SetType(Int2 pos, byte _type)
{
	type[pos.y][pos.x] = _type;
	switch (type[pos.y][pos.x])
	{
		case DIRT:
		case GRASS:
			blockHp[pos.y][pos.x] = 3;
			break;
		case ROCK:
			blockHp[pos.y][pos.x] = 6;
			break;
		case TOUCH:
		case FLOWER:
			blockHp[pos.y][pos.x] = 1;
			break;
		default:
			blockHp[pos.y][pos.x] = 0;
			break;
	}
}

byte Map::GetType(Int2 pos)
{
	return type[pos.y][pos.x];
}
