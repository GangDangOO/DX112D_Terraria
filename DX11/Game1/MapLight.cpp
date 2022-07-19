#include "stdafx.h"

#define MAXLIGHT 20

MapLight::MapLight(Int2 mapsize)
{
	mapSize = mapsize;
	lightPower = new int * [mapSize.y];
	for (int i = 0; i < mapSize.y; i++) {
		lightPower[i] = new int[mapSize.x];
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
				lightPower[i][j] = 0;
			}
			else {
				lightPower[i][j] = MAXLIGHT;
			}
		}
	}
}

void MapLight::SpreadLight(Int2 pos, ObTileMap* block, ObTileMap* _shadow)
{
	queue<Int2> lightPoint;
	lightPoint.push(pos);
	while (!lightPoint.empty()) {
		Int2 l = lightPoint.front();
		_shadow->SetLight(l, lightPower[l.y][l.x]);
		lightPoint.pop();
		if (l.x > 0) {
			int pointPower = lightPower[l.y][l.x];
			Int2 leftPos = Int2(l.x - 1, l.y);
			if (block->GetTileState(leftPos) == TILE_WALL)
				pointPower += 5;
			else
				pointPower += 2;
			if (pointPower > MAXLIGHT)
				pointPower = MAXLIGHT;
			if (pointPower < lightPower[leftPos.y][leftPos.x]) {
				lightPower[leftPos.y][leftPos.x] = pointPower;
				lightPoint.push(leftPos);
			}
		}
		if (l.y > 0) {
			int pointPower = lightPower[l.y][l.x];
			Int2 downPos = Int2(l.x, l.y - 1);
			if (block->GetTileState(downPos) == TILE_WALL)
				pointPower += 5;
			else
				pointPower += 2;
			if (pointPower > MAXLIGHT)
				pointPower = MAXLIGHT;
			if (pointPower < lightPower[downPos.y][downPos.x]) {
				lightPower[downPos.y][downPos.x] = pointPower;
				lightPoint.push(downPos);
			}
		}
		if (l.x < mapSize.x - 1) {
			int pointPower = lightPower[l.y][l.x];
			Int2 rightPos = Int2(l.x + 1, l.y);
			if (block->GetTileState(rightPos) == TILE_WALL)
				pointPower += 5;
			else
				pointPower += 2;
			if (pointPower > MAXLIGHT)
				pointPower = MAXLIGHT;
			if (pointPower < lightPower[rightPos.y][rightPos.x]) {
				lightPower[rightPos.y][rightPos.x] = pointPower;
				lightPoint.push(rightPos);
			}
		}
		if (l.y < mapSize.y - 1) {
			int pointPower = lightPower[l.y][l.x];
			Int2 upPos = Int2(l.x, l.y + 1);
			if (block->GetTileState(upPos) == TILE_WALL)
				pointPower += 5;
			else
				pointPower += 2;
			if (pointPower > MAXLIGHT)
				pointPower = MAXLIGHT;
			if (pointPower < lightPower[upPos.y][upPos.x]) {
				lightPower[upPos.y][upPos.x] = pointPower;
				lightPoint.push(upPos);
			}
		}
	}
}

void MapLight::RemoveLight(Int2 pos, ObTileMap* _shadow)
{
	if (pos.x - 1 < 0 || pos.y - 1 < 0 ||
		pos.x + 1 == mapSize.x || pos.y + 1 == mapSize.y) return;
	if (lightPower[pos.y][pos.x] == 0) return;
	lightPower[pos.y][pos.x] = MAXLIGHT;
	_shadow->SetLight(pos, MAXLIGHT);
}
