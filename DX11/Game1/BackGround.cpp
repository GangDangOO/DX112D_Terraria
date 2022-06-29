#include "stdafx.h"

BackGround::BackGround(Vector2 size)
{
	sky = new ObImage(L"Background_0.png");
	sky->scale = size;
	sky->SetWorldPos(Vector2(-App.GetHalfWidth(), 0.0f));

	mount = new ObImage * [2];
	mount[0] = new ObImage(L"Background_1.png");
	mount[1] = new ObImage(L"Background_2.png");
	for (int i = 0; i < 2; i++) {
		// mount[i]->space = SPACE::SCREEN;
		mount[i]->scale = Vector2(App.GetWidth(), App.GetHeight());
		mount[i]->SetWorldPos(Vector2(CAM->position.x, size.y * 0.2f));
	}
}

BackGround::~BackGround()
{
	SafeDelete(sky);
	for (int i = 0; i < 2; i++) {
		SafeDelete(mount[i]);
	}
	SafeDelete(mount);
}

void BackGround::Update()
{
	sky->Update();
	for (int i = 0; i < 2; i++) {
		mount[i]->SetWorldPosX(CAM->position.x);
		mount[i]->uv.x = 0 + (CAM->position.x / App.GetWidth()) * (i + 1) * 0.2;
		mount[i]->uv.z = 1 + (CAM->position.x / App.GetWidth()) * (i + 1) * 0.2;
		mount[i]->Update();
	}
}

void BackGround::Render()
{
	sky->Render();
	for (int i = 0; i < 2; i++) {
		mount[i]->Render();
	}
}
