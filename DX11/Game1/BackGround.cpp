#include "stdafx.h"

BackGround::BackGround(Vector2 size)
{
	sky = new ObImage(L"Background_0.png");
	sky->scale = size;
	sky->SetWorldPos(Vector2(-App.GetHalfWidth(), 0.0f));
}

BackGround::~BackGround()
{
	SafeDelete(sky);
}

void BackGround::Update()
{
	sky->SetWorldPos(Vector2(CAM->position.x, sky->GetWorldPos().y));

	sky->Update();
}

void BackGround::Render()
{
	sky->Render();
}
