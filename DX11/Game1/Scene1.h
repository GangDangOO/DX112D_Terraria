#pragma once
class Scene1 : public Scene
{
private:
	Int2 mapSize;
	Map* map;
	ObTileMap* block;
public:
	Scene1();
	~Scene1();
	
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;
};


