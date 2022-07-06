#include "stdafx.h"

void Tilebuild::DirtToGrass(ObTileMap& block, Int2 pos, byte** mapLight)
{
	float light = mapLight[pos.y][pos.x] * 0.05f;
	Color color = Color(light, light, light);
	bool l = false, r = false, u = false, d = false;
	int n = 0;
	if (block.GetTileState(Int2(pos.x - 1, pos.y)) == TILE_NONE ||
		pos.x - 1 < 0)
		l = true;

	if (block.GetTileState(Int2(pos.x + 1, pos.y)) == TILE_NONE ||
		pos.x + 1 == block.tileSize.x)
		r = true;

	if (block.GetTileState(Int2(pos.x, pos.y - 1)) == TILE_NONE ||
		pos.y - 1 < 0)
		d = true;

	if (block.GetTileState(Int2(pos.x, pos.y + 1)) == TILE_NONE ||
		pos.y + 1 == block.tileSize.y)
		u = true;

	if (!l && !r && !u && !d) n = 0;
	else if (l && r && u && d) n = 5;
	else if (d && l && u) n = 14;
	else if (r && d && l) n = 12;
	else if (u && r && d) n = 16;
	else if (l && u && r) n = 18;
	else if (u && d) n = 28;
	else if (l && r) n = 46;
	else if (d && l) n = 1;
	else if (r && d) n = 3;
	else if (u && r) n = 9;
	else if (l && u) n = 7;
	else if (d) n = 2;
	else if (u) n = 8;
	else if (r) n = 6;
	else if (l) n = 4;
	if (n != 5) {
		switch (n)
		{
		case 1:
			block.SetTile(pos, Int2(0, 4), GRASS, TILE_WALL, color);
			break;
		case 2:
			block.SetTile(pos, Int2(2, 2), GRASS, TILE_WALL, color);
			break;
		case 3:
			block.SetTile(pos, Int2(1, 4), GRASS, TILE_WALL, color);
			break;
		case 4:
			block.SetTile(pos, Int2(0, 1), GRASS, TILE_WALL, color);
			break;
		case 6:
			block.SetTile(pos, Int2(4, 1), GRASS, TILE_WALL, color);
			break;
		case 7:
			block.SetTile(pos, Int2(0, 3), GRASS, TILE_WALL, color);
			break;
		case 8:
			block.SetTile(pos, Int2(2, 0), GRASS, TILE_WALL, color);
			if (block.GetTileState(Int2(pos.x, pos.y + 1)) == TILE_NONE) {
				int n = RANDOM->Int(1, 6);
				if (n == 6) {
					int rd = RANDOM->Int(0, 44);
					float light = mapLight[pos.y + 1][pos.x] * 0.05f;
					Color fColor = Color(light, light, light);
					block.SetTile(Int2(pos.x, pos.y + 1), Int2(rd, 0), FLOWER, 0, fColor);
				}
			}
			break;
		case 9:
			block.SetTile(pos, Int2(1, 3), GRASS, TILE_WALL, color);
			break;
		case 18:
			block.SetTile(pos, Int2(6, 0), GRASS, TILE_WALL, color);
			break;
		case 16:
			block.SetTile(pos, Int2(12, 0), GRASS, TILE_WALL, color);
			break;
		case 12:
			block.SetTile(pos, Int2(6, 3), GRASS, TILE_WALL, color);
			break;
		case 14:
			block.SetTile(pos, Int2(9, 0), GRASS, TILE_WALL, color);
			break;
		case 28:
			block.SetTile(pos, Int2(7, 4), GRASS, TILE_WALL, color);
			break;
		case 46:
			block.SetTile(pos, Int2(5, 1), GRASS, TILE_WALL, color);
			break;
		default:
			break;
		}
	}
}

void Tilebuild::TileRemove(ObTileMap& block, Int2 tilePos, Map& map, byte** mapLight, bool** wall)
{
	block.SetTile(tilePos, Int2(1, 1), 1, TILE_NONE);
	map.SetType(tilePos, AIR);
	if (wall[tilePos.y][tilePos.x] == false)
		mapLight[tilePos.y][tilePos.x] = 10;
	else
		mapLight[tilePos.y][tilePos.x] = 0;
	float light = mapLight[tilePos.y][tilePos.x] * 0.05f;
	block.SetLight(tilePos, mapLight[tilePos.y][tilePos.x]);
	TileArrangement(block, Int2(tilePos.x - 1, tilePos.y), map.GetType(Int2(tilePos.x - 1, tilePos.y)), map, mapLight);
	TileArrangement(block, Int2(tilePos.x + 1, tilePos.y), map.GetType(Int2(tilePos.x + 1, tilePos.y)), map, mapLight);
	TileArrangement(block, Int2(tilePos.x, tilePos.y - 1), map.GetType(Int2(tilePos.x, tilePos.y - 1)), map, mapLight);
	TileArrangement(block, Int2(tilePos.x, tilePos.y + 1), map.GetType(Int2(tilePos.x, tilePos.y + 1)), map, mapLight);
}

void Tilebuild::TileAdd(ObTileMap& block, Int2 tilePos, Map& map, byte type, byte** mapLight)
{
	float light = mapLight[tilePos.y][tilePos.x] * 0.05f;
	if (type == TOUCH) {
		block.SetTile(tilePos, Int2(0, 0), type);
		if (mapLight[tilePos.y][tilePos.x] < 10) mapLight[tilePos.y][tilePos.x] = 10;
	}
	else {
		mapLight[tilePos.y][tilePos.x] = 0;
		block.SetTileState(tilePos, TILE_WALL);
		map.SetType(tilePos, type);
		TileArrangement(block, Int2(tilePos.x, tilePos.y), map.GetType(tilePos), map, mapLight);
		TileArrangement(block, Int2(tilePos.x - 1, tilePos.y), map.GetType(Int2(tilePos.x - 1, tilePos.y)), map, mapLight);
		TileArrangement(block, Int2(tilePos.x + 1, tilePos.y), map.GetType(Int2(tilePos.x + 1, tilePos.y)), map, mapLight);
		TileArrangement(block, Int2(tilePos.x, tilePos.y - 1), map.GetType(Int2(tilePos.x, tilePos.y - 1)), map, mapLight);
		TileArrangement(block, Int2(tilePos.x, tilePos.y + 1), map.GetType(Int2(tilePos.x, tilePos.y + 1)), map, mapLight);
	}
}

void Tilebuild::TileArrangement(ObTileMap& block, Int2 pos, byte type, Map& map, byte** mapLight)
{
	float light = mapLight[pos.y][pos.x] * 0.05f;
	Color color = Color(light, light, light);
	if (block.GetTileState(pos) == TileState::TILE_WALL) {
		bool l = false, r = false, u = false, d = false;
		int n = 0;
		if (block.GetTileState(Int2(pos.x - 1, pos.y)) == TILE_NONE)
			l = true;

		if (block.GetTileState(Int2(pos.x + 1, pos.y)) == TILE_NONE)
			r = true;

		if (block.GetTileState(Int2(pos.x, pos.y - 1)) == TILE_NONE)
			d = true;

		if (block.GetTileState(Int2(pos.x, pos.y + 1)) == TILE_NONE)
			u = true;

		if (!l && !r && !u && !d) n = 0;
		else if (l && r && u && d) n = 5;
		else if (d && l && u) n = 14;
		else if (r && d && l) n = 12;
		else if (u && r && d) n = 16;
		else if (l && u && r) n = 18;
		else if (u && d) n = 28;
		else if (l && r) n = 46;
		else if (d && l) n = 1;
		else if (r && d) n = 3;
		else if (u && r) n = 9;
		else if (l && u) n = 7;
		else if (d) n = 2;
		else if (u) n = 8;
		else if (r) n = 6;
		else if (l) n = 4;
		switch (n)
		{
		case 0:
			if (map.GetType(pos) == ROCK) {
				l = r = d = u = false;
				if (map.GetType(Int2(pos.x - 1, pos.y)) == DIRT ||
					pos.x - 1 < 0)
					l = true;

				if (map.GetType(Int2(pos.x + 1, pos.y)) == DIRT ||
					pos.x + 1 == block.tileSize.x)
					r = true;
				if (map.GetType(Int2(pos.x, pos.y - 1)) == DIRT ||
					pos.y - 1 < 0)
					d = true;

				if (map.GetType(Int2(pos.x, pos.y + 1)) == DIRT ||
					pos.y + 1 == block.tileSize.y)
					u = true;

				if (l && r && d && u) block.SetTile(pos, Int2(6, 11), type, TILE_WALL, color);
				else if (!l && !r && !d && !u) block.SetTile(pos, Int2(1, 1), type, TILE_WALL, color);
				else if (l && u && r) block.SetTile(pos, Int2(11, 5), type, TILE_WALL, color);
				else if (l && d && r) block.SetTile(pos, Int2(11, 8), type, TILE_WALL, color);
				else if (l && u && d) block.SetTile(pos, Int2(12, 5), type, TILE_WALL, color);
				else if (r && u && d) block.SetTile(pos, Int2(12, 8), type, TILE_WALL, color);
				else if (l && r) block.SetTile(pos, Int2(10, 7), type, TILE_WALL, color);
				else if (u && d) block.SetTile(pos, Int2(9, 10), type, TILE_WALL, color);
				else if (l && u) block.SetTile(pos, Int2(2, 5), type, TILE_WALL, color);
				else if (u && r) block.SetTile(pos, Int2(3, 5), type, TILE_WALL, color);
				else if (r && d) block.SetTile(pos, Int2(3, 6), type, TILE_WALL, color);
				else if (d && l) block.SetTile(pos, Int2(2, 6), type, TILE_WALL, color);
				else if (l) block.SetTile(pos, Int2(9, 7), type, TILE_WALL, color);
				else if (r) block.SetTile(pos, Int2(8, 7), type, TILE_WALL, color);
				else if (u) block.SetTile(pos, Int2(8, 6), type, TILE_WALL, color);
				else if (d) block.SetTile(pos, Int2(8, 5), type, TILE_WALL, color);
			}
			else
				block.SetTile(pos, Int2(1, 1), type, TILE_WALL, color);
			break;
		case 1:
			block.SetTile(pos, Int2(0, 4), type, TILE_WALL, color);
			break;											
		case 2:												
			block.SetTile(pos, Int2(2, 2), type, TILE_WALL, color);
			break;											
		case 3:												
			block.SetTile(pos, Int2(1, 4), type, TILE_WALL, color);
			break;											
		case 4:												
			block.SetTile(pos, Int2(0, 1), type, TILE_WALL, color);
			break;											
		case 5:												
			block.SetTile(pos, Int2(9, 3), type, TILE_WALL, color);
			break;											
		case 6:												
			block.SetTile(pos, Int2(4, 1), type, TILE_WALL, color);
			break;											
		case 7:												
			block.SetTile(pos, Int2(0, 3), type, TILE_WALL, color);
			break;											
		case 8:												
			block.SetTile(pos, Int2(2, 0), type, TILE_WALL, color);
			break;											
		case 9:												
			block.SetTile(pos, Int2(1, 3), type, TILE_WALL, color);
			break;											
		case 18:											
			block.SetTile(pos, Int2(6, 0), type, TILE_WALL, color);
			break;												  
		case 16:												  
			block.SetTile(pos, Int2(12, 0), type, TILE_WALL, color);
			break;												  
		case 12:												  
			block.SetTile(pos, Int2(6, 3), type, TILE_WALL, color);
			break;											
		case 14:											
			block.SetTile(pos, Int2(9, 0), type, TILE_WALL, color);
			break;											
		case 28:											
			block.SetTile(pos, Int2(7, 4), type, TILE_WALL, color);
			break;											
		case 46:											
			block.SetTile(pos, Int2(5, 1), type, TILE_WALL, color);
			break;
		default:
			break;
		}
	}
}
