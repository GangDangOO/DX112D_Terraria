#pragma once

enum class ANIM
{
	IDLE,
	MOVE,
	JUMP
};
class Player : public Character
{
private:
	float playerMaxSpeed;
	float playerBoostSpeed;
	Vector2 move;

	bool isJump;
public:
	ANIM anim;
	ObImage* playerSprite;
	Player(ObTileMap* _tileMap);
	~Player();
	void Action();
	void ChangeStat(ANIM stat);
	bool Run();
	bool fall();
	void Update();
	void Render();
};

