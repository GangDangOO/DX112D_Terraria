#pragma once
class MapWall
{
private:
	Int2 mapSize;
public:
	bool** isWall;
	MapWall(Int2 mapsize);
	~MapWall();
};

