#include "stdafx.h"

Map::Map(Int2 MapSize, unsigned int Seed)
{
	tileSize = MapSize;
	PerlinNoise pn(Seed);
	type = new Type * [tileSize.y];
	for (int i = 0; i < tileSize.y; i++) {
		type[i] = new Type[tileSize.x];
	}
	for (int i = 0; i < tileSize.y; ++i) {
		for (int j = 0; j < tileSize.x; ++j) {
			if (i < tileSize.y * 0.9) {
				double x = (double)j / ((double)tileSize.x);
				double y = (double)i / ((double)tileSize.y);

				double n = pn.noise(50 * x, 20 * y, 0.65);

				if (n > 0.5f) {
					type[i][j] = AIR;
				}
				else {
					type[i][j] = WALL;
				}
			}
			else {
				type[i][j] = WALL;
			}
		}
	}
	isRectVisible = false;
	CellularAutomata();
	CellularAutomata();
	CellularAutomata();
}

Map::~Map()
{
}

void Map::Release()
{
	for (int i = 0; i < tileSize.y; i++) {
		SafeDelete(type[i]);
	}
	SafeDelete(type);
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

void Map::CellularAutomata()
{
	for (int i = 1; i < tileSize.y - 1; ++i) {
		for (int j = 1; j < tileSize.x - 1; ++j) {
			if (type[i][j] == AIR) {
				int count = 0;
				if (type[i + 1][j - 1] == WALL) count++;
				if (type[i + 1][j] == WALL) count++;
				if (type[i + 1][j + 1] == WALL) count++;
				if (type[i][j - 1] == WALL) count++;
				if (type[i][j + 1] == WALL) count++;
				if (type[i - 1][j - 1] == WALL) count++;
				if (type[i - 1][j] == WALL) count++;
				if (type[i - 1][j + 1] == WALL) count++;
				if (count >= 5) {
					type[i][j] = WALL;
				}
			}
		}
	}
}

bool Map::IsThisWall(Int2 pos)
{
	return type[pos.y][pos.x] == Type::WALL;
}
