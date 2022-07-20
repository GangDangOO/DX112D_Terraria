#pragma once
class Zombie : public Character
{
private:
	float jumpTime;
public:
	ObRect* playerCol;
	Zombie(ObTileMap* _tileMap);
	~Zombie();
	bool Fall();
	bool Jump();
	bool Move();
	void Update();
	void Render();
};

