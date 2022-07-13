#pragma once
enum PHYSICSDIR {
	LEFT_1,
	LEFT_2,
	LEFT_3,
	RIGHT_1,
	RIGHT_2,
	RIGHT_3,
	DOWN_L,
	DOWN_R,
	UP_L,
	UP_R
};
struct Bool4 {
	bool left = false;
	bool right = false;
	bool up = false;
	bool down = false;
};
struct Status
{
	int hp;
	int def;
	int atk;
};
class Character
{
public:
	Status stat;
	ObImage* bodySprite;
	ObRect* col;

	ObTileMap* tileMap;
	bool isCheckBlock[12];
	Bool4 dirCheck;
	Vector2 move;
	Character();
	~Character();
	void IsBlockUpdate();
	void Update();
};

