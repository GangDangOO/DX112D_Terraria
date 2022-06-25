#pragma once
enum Type
{
	AIR,
	WALL
};
class Map
{
private:
	Int2 tileSize;
	Type** type;
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

