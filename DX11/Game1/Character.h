#pragma once
struct Status
{
	int hp;
	int def;
	int atk;
};
class Character
{
public:
	ObTileMap* tileMap;
	Status stat;
	ObRect* col;
	Character();
	~Character();
};

