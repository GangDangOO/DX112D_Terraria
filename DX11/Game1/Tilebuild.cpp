#include "stdafx.h"

void Tilebuild::TileRemove(ObTileMap& block, Int2 tilePos, Map& map)
{
	block.SetTile(tilePos, Int2(1, 1), 1, TILE_NONE);
	TileArrangement(block, Int2(tilePos.x - 1, tilePos.y), map.GetType(Int2(tilePos.x - 1, tilePos.y)));
	TileArrangement(block, Int2(tilePos.x + 1, tilePos.y), map.GetType(Int2(tilePos.x + 1, tilePos.y)));
	TileArrangement(block, Int2(tilePos.x, tilePos.y - 1), map.GetType(Int2(tilePos.x, tilePos.y - 1)));
	TileArrangement(block, Int2(tilePos.x, tilePos.y + 1), map.GetType(Int2(tilePos.x, tilePos.y + 1)));
}

void Tilebuild::TileAdd(ObTileMap& block, Int2 tilePos, Map& map)
{
	block.SetTileState(tilePos, TILE_WALL);
	TileArrangement(block, Int2(tilePos.x, tilePos.y), map.GetType(tilePos));
	TileArrangement(block, Int2(tilePos.x - 1, tilePos.y), map.GetType(Int2(tilePos.x - 1, tilePos.y)));
	TileArrangement(block, Int2(tilePos.x + 1, tilePos.y), map.GetType(Int2(tilePos.x + 1, tilePos.y)));
	TileArrangement(block, Int2(tilePos.x, tilePos.y - 1), map.GetType(Int2(tilePos.x, tilePos.y - 1)));
	TileArrangement(block, Int2(tilePos.x, tilePos.y + 1), map.GetType(Int2(tilePos.x, tilePos.y + 1)));
}

void Tilebuild::TileArrangement(ObTileMap& block, Int2 pos, byte type)
{
	if (block.GetTileState(pos) == TileState::TILE_WALL) {
		bool l = false, r = false, u = false, d = false;
		int n = 0;
		if (block.GetTileState(Int2(pos.x - 1, pos.y)) == TileState::TILE_NONE) l = true;
		if (block.GetTileState(Int2(pos.x + 1, pos.y)) == TileState::TILE_NONE) r = true;
		if (block.GetTileState(Int2(pos.x, pos.y - 1)) == TileState::TILE_NONE) d = true;
		if (block.GetTileState(Int2(pos.x, pos.y + 1)) == TileState::TILE_NONE) u = true;
		if (l) n = 4;
		if (r) n = 6;
		if (u) n = 8;
		if (d) n = 2;
		if (l && u) n = 7;
		if (u && r) n = 9;
		if (r && d) n = 3;
		if (d && l) n = 1;
		if (l && r) n = 46;
		if (u && d) n = 28;
		if (l && u && r) n = 18;
		if (u && r && d) n = 16;
		if (r && d && l) n = 12;
		if (d && l && u) n = 14;
		if (l && r && u && d) n = 5;
		if (!l && !r && !u && !d) n = 0;
		switch (n)
		{
		case 0:
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
