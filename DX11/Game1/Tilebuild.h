#pragma once

class Tilebuild
{
public:
	void DirtToGrass(ObTileMap& block, Int2 pos, byte** mapLight);
	void TileRemove(ObTileMap& block, Int2 tilePos, Map& map, byte** mapLight);
	void TileAdd(ObTileMap& block, Int2 tilePos, Map& map, byte type, byte** mapLight);
	void TileArrangement(ObTileMap& block, Int2 pos, byte type, Map& map, byte** mapLight);
};

