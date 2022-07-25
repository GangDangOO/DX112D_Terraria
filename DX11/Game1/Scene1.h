#pragma once
class Scene1 : public Scene
{
private:
	Int2 mapSize;
	Map* map;
	ObTileMap* block;
	ObTileMap* wall;
	ObTileMap* shadow;
	MapWall* mapWall;
	MapLight* mapLight;
	BackGround* bg;
	Tilebuild tb;
	Player* player;
	Slime* slime[5];
	Zombie* zombie[5];
	Boss* boss;
	bool camMod;
	bool shadowMod;
public:
	Scene1();
	~Scene1();
	
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;
};


