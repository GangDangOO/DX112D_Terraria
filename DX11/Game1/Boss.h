#pragma once
class Boss : public Character
{
public:
	ObRect* playerCol;
	Vector2 patrol_1, look;
	float dashTime, phaseTime;
	bool isPhase, isAtk;
	int atkN;
	Boss(ObTileMap* _tileMap);
	~Boss();

	void Move();
	void Dash();
	void Update();
	void Render();
};

