#pragma once
class Slime : public Character
{
public:
	Slime(ObTileMap* _tileMap);
	~Slime();
	void Update();
	void Render();
};

