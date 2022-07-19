#pragma once
enum Type
{
	DIRT,
	AIR,
	ROCK,
	GRASS,
	FLOWER,
	TOUCH,
	WALL
};
class Map
{
private:
	Int2	tileSize;
	byte**	type;
	int**	blockHp;
	bool	isRectVisible;
public:
	Map(Int2 MapSize, unsigned int Seed);
	~Map();
	void Release();
	void Update();
	void LateUpdate();
	void Render();
	bool MiningBlock(Int2 pos);
	void CellularAutomata();
	void SetType(Int2 pos, byte _type);
	byte GetType(Int2 pos);
};

