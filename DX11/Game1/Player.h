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
public:
	ANIM anim;
	Player(ObTileMap* _tileMap);
	~Player();
	void Action();
	void ChangeStat(ANIM stat);
	bool Run();
	bool fall();
	void Update();
	void Render();
};

