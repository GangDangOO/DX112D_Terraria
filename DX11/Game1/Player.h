#pragma once
enum ANIM
{
	IDLE,
	MOVE,
	JUMP
};
class Player : public Character
{
public:
	ANIM anim;
	ObImage* playerSprite;
	Player();
	~Player();
	void Action();
	void Update();
	void Render();
};

