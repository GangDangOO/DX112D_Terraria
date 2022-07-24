#pragma once
class Slime : public Character
{
public:
	ObRect* playerCol;
	float atkTime;
	float coolTime;
	Slime(ObTileMap* _tileMap);
	~Slime();

	bool Fall();
	bool Jump();
	void Update();
	void Render();
};

