#pragma once

enum class ANIM
{
	IDLE,
	MOVE,
	JUMP,
	ITEM
};

enum class ITEM {
	NOT,
	BLOCK,
	TOUCH,
	PICK,
	SWORD,
	BOW,
	MAGIC
};
class Player : public Character
{
private:
	float	playerMaxSpeed;
	float	playerBoostSpeed;
	float	jumpTime;
	float	blockMiningTime;
public:
	Map*	map;
	MapLight* mapLight;
	ObTileMap* shadow;
	bool** isWall;
	ITEM	itemSlot;
	ANIM anim;
	Player(ObTileMap* _tileMap);
	~Player();
	void Action();
	void ChangeStat(ANIM stat);
	bool Run();
	bool fall();
	bool UseItem();
	void ChangeSlot();
	void Update();
	void Render();
};

