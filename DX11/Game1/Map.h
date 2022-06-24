#pragma once
enum Type
{
	AIR,
	WALL
};
struct Tile
{
	Type type;
	ObRect tile;
};
class Map
{
private:
	Int2 tileSize;
	Tile** map;
public:
	Map(Int2 MapSize, unsigned int Seed);
	~Map();
	void Release();
	void Update();
	void LateUpdate();
	void Render();
	void CellularAutomata();
};

