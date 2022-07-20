#pragma once
enum PHYSICSDIR {
	LEFT_D,
	LEFT_U,
	RIGHT_D,
	RIGHT_U,
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
	int knockBack;
};
class Character
{
public:
	Status stat;
	ObImage* bodySprite;
	ObRect* col;

	ObTileMap* tileMap;
	bool isCheckBlock[8];
	ObRect blockCol[8];
	Bool4 dirCheck;
	Vector2 move;
	Character();
	~Character();
	void Spawn();
	void Spawn(Vector2 playerPos);
	void IsBlockUpdate();
	void Update();
	void LateUpdate();
	void Render();
};

