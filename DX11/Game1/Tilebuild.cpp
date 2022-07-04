#include "stdafx.h"

void Tilebuild::DirtToGrass(ObTileMap& block, Int2 pos)
{
	bool l = false, r = false, u = false, d = false;
	int n = 0;
	if (block.GetTileState(Int2(pos.x - 1, pos.y)) == TILE_NONE) l = true;
	if (block.GetTileState(Int2(pos.x + 1, pos.y)) == TILE_NONE) r = true;
	if (block.GetTileState(Int2(pos.x, pos.y - 1)) == TILE_NONE) d = true;
	if (block.GetTileState(Int2(pos.x, pos.y + 1)) == TILE_NONE) u = true;
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
			block.SetTile(pos, Int2(0, 4), GRASS, TILE_WALL);
			break;
		case 2:
			block.SetTile(pos, Int2(2, 2), GRASS, TILE_WALL);
			break;
		case 3:
			block.SetTile(pos, Int2(1, 4), GRASS, TILE_WALL);
			break;
		case 4:
			block.SetTile(pos, Int2(0, 1), GRASS, TILE_WALL);
			break;
		case 6:
			block.SetTile(pos, Int2(4, 1), GRASS, TILE_WALL);
			break;
		case 7:
			block.SetTile(pos, Int2(0, 3), GRASS, TILE_WALL);
			break;
		case 8:
			block.SetTile(pos, Int2(2, 0), GRASS, TILE_WALL);
			if (block.GetTileState(Int2(pos.x, pos.y + 1)) == TILE_NONE) {
				int n = RANDOM->Int(1, 6);
				if (n == 6) {
					int rd = RANDOM->Int(0, 44);
					block.SetTile(Int2(pos.x, pos.y + 1), Int2(rd, 0), FLOWER);
				}
			}
			break;
		case 9:
			block.SetTile(pos, Int2(1, 3), GRASS, TILE_WALL);
			break;
		case 18:
			block.SetTile(pos, Int2(6, 0), GRASS, TILE_WALL);
			break;
		case 16:
			block.SetTile(pos, Int2(12, 0), GRASS, TILE_WALL);
			break;
		case 12:
			block.SetTile(pos, Int2(6, 3), GRASS, TILE_WALL);
			break;
		case 14:
			block.SetTile(pos, Int2(9, 0), GRASS, TILE_WALL);
			break;
		case 28:
			block.SetTile(pos, Int2(7, 4), GRASS, TILE_WALL);
			break;
		case 46:
			block.SetTile(pos, Int2(5, 1), GRASS, TILE_WALL);
			break;
		default:
			break;
		}
	}
}

void Tilebuild::TileRemove(ObTileMap& block, Int2 tilePos, Map& map)
{
	block.SetTile(tilePos, Int2(1, 1), 1, TILE_NONE);
	map.SetType(tilePos, AIR);
	TileArrangement(block, Int2(tilePos.x - 1, tilePos.y), map.GetType(Int2(tilePos.x - 1, tilePos.y)), map);
	TileArrangement(block, Int2(tilePos.x + 1, tilePos.y), map.GetType(Int2(tilePos.x + 1, tilePos.y)), map);
	TileArrangement(block, Int2(tilePos.x, tilePos.y - 1), map.GetType(Int2(tilePos.x, tilePos.y - 1)), map);
	TileArrangement(block, Int2(tilePos.x, tilePos.y + 1), map.GetType(Int2(tilePos.x, tilePos.y + 1)), map);
}

void Tilebuild::TileAdd(ObTileMap& block, Int2 tilePos, Map& map, byte type)
{
	if (type == TOUCH) {
		block.SetTile(tilePos, Int2(0, 0), type);
	}
	else {
		block.SetTileState(tilePos, TILE_WALL);
		map.SetType(tilePos, type);
		TileArrangement(block, Int2(tilePos.x, tilePos.y), map.GetType(tilePos), map);
		TileArrangement(block, Int2(tilePos.x - 1, tilePos.y), map.GetType(Int2(tilePos.x - 1, tilePos.y)), map);
		TileArrangement(block, Int2(tilePos.x + 1, tilePos.y), map.GetType(Int2(tilePos.x + 1, tilePos.y)), map);
		TileArrangement(block, Int2(tilePos.x, tilePos.y - 1), map.GetType(Int2(tilePos.x, tilePos.y - 1)), map);
		TileArrangement(block, Int2(tilePos.x, tilePos.y + 1), map.GetType(Int2(tilePos.x, tilePos.y + 1)), map);
	}
}

void Tilebuild::TileArrangement(ObTileMap& block, Int2 pos, byte type, Map& map)
{
	if (block.GetTileState(pos) == TileState::TILE_WALL) {
		bool l = false, r = false, u = false, d = false;
		int n = 0;
		if (block.GetTileState(Int2(pos.x - 1, pos.y)) == TILE_NONE) l = true;
		if (block.GetTileState(Int2(pos.x + 1, pos.y)) == TILE_NONE) r = true;
		if (block.GetTileState(Int2(pos.x, pos.y - 1)) == TILE_NONE) d = true;
		if (block.GetTileState(Int2(pos.x, pos.y + 1)) == TILE_NONE) u = true;
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
				if (map.GetType(Int2(pos.x - 1, pos.y)) == DIRT) l = true;
				if (map.GetType(Int2(pos.x + 1, pos.y)) == DIRT) r = true;
				if (map.GetType(Int2(pos.x, pos.y - 1)) == DIRT) d = true;
				if (map.GetType(Int2(pos.x, pos.y + 1)) == DIRT) u = true;
				if (l && r && d && u) block.SetTile(pos, Int2(6, 11), type, TILE_WALL);
				else if (!l && !r && !d && !u) block.SetTile(pos, Int2(1, 1), type, TILE_WALL);
				else if (l && u && r) block.SetTile(pos, Int2(11, 5), type, TILE_WALL);
				else if (l && d && r) block.SetTile(pos, Int2(11, 8), type, TILE_WALL);
				else if (l && u && d) block.SetTile(pos, Int2(12, 5), type, TILE_WALL);
				else if (r && u && d) block.SetTile(pos, Int2(12, 8), type, TILE_WALL);
				else if (l && r) block.SetTile(pos, Int2(10, 7), type, TILE_WALL);
				else if (u && d) block.SetTile(pos, Int2(9, 10), type, TILE_WALL);
				else if (l && u) block.SetTile(pos, Int2(2, 5), type, TILE_WALL);
				else if (u && r) block.SetTile(pos, Int2(3, 5), type, TILE_WALL);
				else if (r && d) block.SetTile(pos, Int2(3, 6), type, TILE_WALL);
				else if (d && l) block.SetTile(pos, Int2(2, 6), type, TILE_WALL);
				else if (l) block.SetTile(pos, Int2(9, 7), type, TILE_WALL);
				else if (r) block.SetTile(pos, Int2(8, 7), type, TILE_WALL);
				else if (u) block.SetTile(pos, Int2(8, 6), type, TILE_WALL);
				else if (d) block.SetTile(pos, Int2(8, 5), type, TILE_WALL);
			}
			else
				block.SetTile(pos, Int2(1, 1), type, TILE_WALL);
			break;
		case 1:
			block.SetTile(pos, Int2(0, 4), type, TILE_WALL);
			break;											
		case 2:												
			block.SetTile(pos, Int2(2, 2), type, TILE_WALL);
			break;											
		case 3:												
			block.SetTile(pos, Int2(1, 4), type, TILE_WALL);
			break;											
		case 4:												
			block.SetTile(pos, Int2(0, 1), type, TILE_WALL);
			break;											
		case 5:												
			block.SetTile(pos, Int2(9, 3), type, TILE_WALL);
			break;											
		case 6:												
			block.SetTile(pos, Int2(4, 1), type, TILE_WALL);
			break;											
		case 7:												
			block.SetTile(pos, Int2(0, 3), type, TILE_WALL);
			break;											
		case 8:												
			block.SetTile(pos, Int2(2, 0), type, TILE_WALL);
			break;											
		case 9:												
			block.SetTile(pos, Int2(1, 3), type, TILE_WALL);
			break;											
		case 18:											
			block.SetTile(pos, Int2(6, 0), type, TILE_WALL);
			break;												  
		case 16:												  
			block.SetTile(pos, Int2(12, 0), type, TILE_WALL);
			break;												  
		case 12:												  
			block.SetTile(pos, Int2(6, 3), type, TILE_WALL);
			break;											
		case 14:											
			block.SetTile(pos, Int2(9, 0), type, TILE_WALL);
			break;											
		case 28:											
			block.SetTile(pos, Int2(7, 4), type, TILE_WALL);
			break;											
		case 46:											
			block.SetTile(pos, Int2(5, 1), type, TILE_WALL);
			break;
		default:
			break;
		}
	}
}
