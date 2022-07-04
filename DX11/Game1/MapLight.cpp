#include "stdafx.h"

MapLight::MapLight(Int2 mapsize)
{
	mapSize = mapsize;
	lightPower = new byte * [mapSize.y];
	for (int i = 0; i < mapSize.x; i++) {
		lightPower[i] = new byte[mapSize.x];
	}
}

MapLight::~MapLight()
{
	for (int i = 0; i < mapSize.x; i++) {
		SafeDelete(lightPower[i]);
	}
	SafeDelete(lightPower);
}

void MapLight::CalcLight(Map* map, ObTileMap* tile)
{
	for (int y = 0; y < mapSize.y; y++) {
		for (int x = 0; x < mapSize.x; x++) {
			if (map->GetType(Int2(x, y)) == AIR) {
				lightPower[y][x] = 5;
			}
			else
				lightPower[y][x] = 0;
		}
	}
}
