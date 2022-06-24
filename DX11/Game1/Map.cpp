#include "stdafx.h"

Map::Map(Int2 MapSize, unsigned int Seed)
{
	tileSize = MapSize;
	map = new Tile * [tileSize.y];
	PerlinNoise pn(Seed);
	for (int i = 0; i < tileSize.y; i++) {
		map[i] = new Tile[tileSize.x];
	}
	for (int i = 0; i < tileSize.y; ++i) {
		for (int j = 0; j < tileSize.x; ++j) {
			double x = (double)j / ((double)tileSize.x);
			double y = (double)i / ((double)tileSize.y);

			double n = pn.noise(100 * x, 100 * y, 0.8);

			if (n > 0.5f) {
				map[i][j].type = AIR;
				n = 1.0;
			}
			else {
				map[i][j].type = WALL;
				n = 0.0;
			}
			map[i][j].tile.colEnable = false;
			map[i][j].tile.scale = Vector2(App.GetWidth() / tileSize.x, App.GetHeight() / tileSize.y);
			map[i][j].tile.SetWorldPos(Vector2(-App.GetHalfWidth() + j * map[i][j].tile.scale.x, -App.GetHalfHeight() + i * map[i][j].tile.scale.y));
			map[i][j].tile.color = Color(n, n, n);
		}
	}
}

Map::~Map()
{
}

void Map::Release()
{
	for (int i = 0; i < tileSize.y; i++) {
		SafeDelete(map[i]);
	}
	SafeDelete(map);
}

void Map::Update()
{
	if (ImGui::Button("CellularAutomata"))
		CellularAutomata();
	for (int i = 0; i < tileSize.y; ++i) {
		for (int j = 0; j < tileSize.x; ++j) {
			map[i][j].tile.Update();
		}
	}
}

void Map::LateUpdate()
{

}

void Map::Render()
{
	for (int i = 0; i < tileSize.y; ++i) {
		for (int j = 0; j < tileSize.x; ++j) {
			map[i][j].tile.Render();
		}
	}
}

void Map::CellularAutomata()
{
	for (int i = 1; i < tileSize.y - 1; ++i) {
		for (int j = 1; j < tileSize.x - 1; ++j) {
			if (map[i][j].type == AIR) {
				int count = 0;
				if (map[i + 1][j - 1].type == WALL) count++;
				if (map[i + 1][j].type == WALL) count++;
				if (map[i + 1][j + 1].type == WALL) count++;
				if (map[i][j - 1].type == WALL) count++;
				if (map[i][j + 1].type == WALL) count++;
				if (map[i - 1][j - 1].type == WALL) count++;
				if (map[i - 1][j].type == WALL) count++;
				if (map[i - 1][j + 1].type == WALL) count++;
				if (count >= 5) {
					map[i][j].type = WALL;
					map[i][j].tile.color = Color(0.0f, 0.0f, 0.0f);
				}
			}
		}
	}
}
