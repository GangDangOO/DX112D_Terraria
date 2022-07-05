#include "stdafx.h"

MapWall::MapWall(Int2 mapsize)
{
	mapSize = mapsize;
	isWall = new bool* [mapSize.y];
	for (int i = 0; i < mapSize.y; i++) {
		isWall[i] = new bool[mapSize.x];
	}
	for (int i = 0; i < mapSize.y; i++) {
		for (int j = 0; j < mapSize.x; j++) {
			if (i < mapSize.y * 0.68) {
				isWall[i][j] = true;
			}
			else {
				isWall[i][j] = false;
			}
		}
	}
}

MapWall::~MapWall()
{
	for (int i = 0; i < mapSize.y; i++)
		SafeDelete(isWall[i]);
	SafeDelete(isWall);
}
