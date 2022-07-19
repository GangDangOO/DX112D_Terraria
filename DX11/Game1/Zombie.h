#pragma once
class Zombie : public Character
{
public:
	ObRect* playerCol;
	Zombie(ObTileMap* _tileMap);
	~Zombie();
	void Update();
	void Render();
};

