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

void MapLight::CalcLight(Map* map, bool** wall)
{
	for (int i = 0; i < mapSize.y; i++) {
		for (int j = 0; j < mapSize.x; j++) {
			if (map->GetType(Int2(j, i)) == AIR &&
				wall[i][j] == false) {
				lightPower[i][j] = 5;
			}
		}
	}
}

byte MapLight::GetLightPower(Int2 pos)
{
	return lightPower[pos.y][pos.x];
}
