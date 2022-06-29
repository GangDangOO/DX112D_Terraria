#pragma once
class BackGround
{
private:
	ObImage* sky;
	ObImage** mount;
	ObImage* cave;
	Vector2 v;
public:
	BackGround(Vector2 size);
	~BackGround();
	void Update();
	void Render();
};

