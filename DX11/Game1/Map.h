#pragma once
enum Type
{
	DIRT,
	AIR,
	ROCK,
	GRASS,
	FLOWER,
	TOUCH
};
class Map
{
private:
	Int2 tileSize;
	byte** type;
	bool isRectVisible;
public:
	Map(Int2 MapSize, unsigned int Seed);
	~Map();
	void Release();
	void Update();
	void LateUpdate();
	void Render();
	void CellularAutomata();
	void SetType(Int2 pos, byte _type);
	byte GetType(Int2 pos);
};

