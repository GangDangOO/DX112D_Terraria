#pragma once
class Tilebuild
{
public:
	void TileRemove(ObTileMap& block, Int2 tilePos);
	void TileAdd(ObTileMap& block, Int2 tilePos, int type);
	void TileArrangement(ObTileMap& block, Int2 pos);
};

