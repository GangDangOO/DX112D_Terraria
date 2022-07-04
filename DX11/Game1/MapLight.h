#pragma once
class MapLight
{
private:
	Int2   mapSize;
	byte** lightPower;
public:
	MapLight(Int2 mapSize);
	~MapLight();
	void CalcLight(Map* map, ObTileMap* tile);
};

