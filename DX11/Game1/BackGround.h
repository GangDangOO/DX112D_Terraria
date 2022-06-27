#pragma once
class BackGround
{
private:
	ObImage* sky;
public:
	BackGround(Vector2 size);
	~BackGround();
	void Update();
	void Render();
};

