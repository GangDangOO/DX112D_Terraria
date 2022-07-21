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

	ObImage* dirt[5];
	ObImage* rock[5];
	float	visibleTime;

	int**	blockHp;
	bool	isRectVisible;
public:
	ObTileMap* tileMap;
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

