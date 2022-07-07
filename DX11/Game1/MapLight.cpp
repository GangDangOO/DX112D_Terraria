#include "stdafx.h"

MapLight::MapLight(Int2 mapsize)
{
	mapSize = mapsize;
	lightPower = new byte * [mapSize.y];
	for (int i = 0; i < mapSize.y; i++) {
		lightPower[i] = new byte[mapSize.x];
	}
	for (int i = 0; i < mapSize.y; i++) {
		for (int j = 0; j < mapSize.x; j++) {
			lightPower[i][j] = 0;
		}
	}
}

MapLight::~MapLight()
{
	for (int i = 0; i < mapSize.y; i++) {
		SafeDelete(lightPower[i]);
	}
	SafeDelete(lightPower);
}

void MapLight::CalcLight(Map* map, bool** wall, ObTileMap* block, ObTileMap* wallM)
{
	for (int i = 0; i < mapSize.y; i++) {
		for (int j = 0; j < mapSize.x; j++) {
			if (map->GetType(Int2(j, i)) == AIR &&
				wall[i][j] == false) {
				lightPower[i][j] = 20;
				SpreadLight(Int2(j, i), block, wallM);
			}
		}
	}
}

float MapLight::GetLightPower(Int2 pos)
{
	return lightPower[pos.y][pos.x] * 0.025f;
}

void MapLight::SpreadLight(Int2 pos, ObTileMap* block, ObTileMap* wall)
{
	if (pos.x - 1 < 0 || pos.y - 1 < 0 ||
		pos.x + 1 == mapSize.x || pos.y + 1 == mapSize.y) return;
	if (lightPower[pos.y][pos.x] == 0) return;
	block->SetLight(pos, lightPower[pos.y][pos.x]);
	wall->SetLight(pos, lightPower[pos.y][pos.x]);

	byte light = lightPower[pos.y][pos.x] - 1;
	if (block->GetTileState(Int2(pos.x, pos.y - 1)) == TILE_WALL && light != 0)
		light--;
	if (lightPower[pos.y - 1][pos.x] < light) {
		lightPower[pos.y - 1][pos.x] = light;
		SpreadLight(Int2(pos.x, pos.y - 1), block, wall);
	}

	light = lightPower[pos.y][pos.x] - 1;
	if (block->GetTileState(Int2(pos.x - 1, pos.y)) == TILE_WALL && light != 0)
		light--;
	if (lightPower[pos.y][pos.x - 1] < light) {
		lightPower[pos.y][pos.x - 1] = light;
		SpreadLight(Int2(pos.x - 1, pos.y), block, wall);
	}

	light = lightPower[pos.y][pos.x] - 1;
	if (block->GetTileState(Int2(pos.x, pos.y + 1)) == TILE_WALL && light != 0)
		light--;
	if (lightPower[pos.y + 1][pos.x] < light) {
		lightPower[pos.y + 1][pos.x] = light;
		SpreadLight(Int2(pos.x, pos.y + 1), block, wall);
	}

	light = lightPower[pos.y][pos.x] - 1;
	if (block->GetTileState(Int2(pos.x + 1, pos.y)) == TILE_WALL && light != 0)
		light--;
	if (lightPower[pos.y][pos.x + 1] < light) {
		lightPower[pos.y][pos.x + 1] = light;
		SpreadLight(Int2(pos.x + 1, pos.y), block, wall);
	}
}

void MapLight::RemoveLight(Int2 pos, ObTileMap* block, ObTileMap* wall)
{
	if (pos.x - 1 < 0 || pos.y - 1 < 0 ||
		pos.x + 1 == mapSize.x || pos.y + 1 == mapSize.y) return;
	if (lightPower[pos.y][pos.x] == 20) return;
		lightPower[pos.y][pos.x] = 0;
}
