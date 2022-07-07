#pragma once
class MapLight
{
private:
	Int2   mapSize;
public:
	byte** lightPower;
	MapLight(Int2 mapSize);
	~MapLight();
	void CalcLight(Map* map, bool** wall, ObTileMap* block, ObTileMap* wallM);
	float GetLightPower(Int2 pos);
	void SpreadLight(Int2 pos, ObTileMap* block, ObTileMap* wall);
	void RemoveLight(Int2 pos, ObTileMap* block, ObTileMap* wall);
};
