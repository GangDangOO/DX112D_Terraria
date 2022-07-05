#pragma once
class MapLight
{
private:
	Int2   mapSize;
public:
	byte** lightPower;
	MapLight(Int2 mapSize);
	~MapLight();
	void CalcLight(Map* map, bool** wall);
	byte GetLightPower(Int2 pos);
};

