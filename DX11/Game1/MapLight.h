#pragma once
class MapLight
{
private:
	Int2   mapSize;
public:
	int** lightPower;
	MapLight(Int2 mapSize);
	~MapLight();
	void CalcLight(Map* map, bool** wall);
	void SpreadLight(Int2 pos, ObTileMap* block, ObTileMap* _shadow);
	void RemoveLight(Int2 pos, ObTileMap* _shadow);
};
