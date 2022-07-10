#pragma once

class Tilebuild
{
public:
	void DirtToGrass(ObTileMap& block, Int2 pos, int** mapLight);
	void TileRemove(ObTileMap& block, Int2 tilePos, Map& map, int** mapLight, bool** wall);
	void TileAdd(ObTileMap& block, Int2 tilePos, Map& map, byte type, int** mapLight);
	void TileArrangement(ObTileMap& block, Int2 pos, byte type, Map& map, int** mapLight);
};

