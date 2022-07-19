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
}

void Map::Update()
{
	if (INPUT->KeyDown('Q')) {
		isRectVisible = !isRectVisible;
	}
}

void Map::LateUpdate()
{

}

void Map::Render()
{
	
}

bool Map::MiningBlock(Int2 pos)
{
	bool isDelete = false;
	blockHp[pos.y][pos.x]--;
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
