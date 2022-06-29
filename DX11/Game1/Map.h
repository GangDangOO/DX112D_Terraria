#pragma once
enum Type
{
	AIR,
	DIRT
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
	bool IsThisWall(Int2 pos);
};

